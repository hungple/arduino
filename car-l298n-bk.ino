// D1 Mini NodeMCU Based WIFI Controlled Car//

#define ENB   4           // L298N ENB Enable/speed Front motors  GPIO4(D2)
#define IN3   2           // L298N IN3 motors Right               GPIO2(D4)
#define IN4   0           // L298N IN4 motors Right               GPIO0(D3)
#define ENA   15          // L298N ENA Enable/speed Back motor    GPIO15(D8)
#define IN1   13          // L298N IN1_1 Back motor               GPIO13(D7)
#define IN2   12          // L298N IN2_1 Back motors              GPIO12(D6)

#include <SoftwareSerial.h>
#include <Ticker.h>

// Load Wi-Fi library
#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid     = "orange";
const char* password = "87511222333";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Watchdog
Ticker secondTick;
volatile int watchdogCount = 0;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

const int MIN_SPEED  = 400;
const int MAX_SPEED  = 1500;
const int STEP_SPEED = 100;
const int TURN_SPEED = 1000;
int curSpeed = MIN_SPEED;


// int back_led = 13;
// int front_led = 12;

void ISRwatchdog() {
  watchdogCount++;
  if(watchdogCount == 5) {
    Serial.println();
    Serial.println("the watchdog bites!!!!!!!!!!!");
    ESP.reset();
  }
}

void setup() {
  Serial.begin(115200);
  secondTick.attach(1, ISRwatchdog);

  // Initialize the output variables as outputs
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);

  // Set outputs to LOW
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite (ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite (ENA, 0);

  // back and front leds
  // pinMode(back_led, OUTPUT);
  // pinMode(front_led, OUTPUT);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();

}

void loop() {

  WiFiClient client = server.available();   // Listen for incoming clients
  watchdogCount = 0;
  if (client) {                             // If a new client connects,

    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Process header/command
            if (header.indexOf("GET /F") >= 0) { // Forward
              Serial.println("F");
              if (curSpeed < MAX_SPEED) {
                curSpeed = curSpeed + STEP_SPEED;
              }
              Serial.println(curSpeed);
              MotorB_Run(curSpeed);
            } else if (header.indexOf("GET /S") >= 0) {
              Serial.println("S");
              if (curSpeed > MIN_SPEED) {
                curSpeed = curSpeed - 2*STEP_SPEED;
                Serial.println(curSpeed);
                MotorB_Run(curSpeed);
              } else {
                MotorB_Run(0);
              }
            } else if (header.indexOf("GET /B") >= 0) { // Reverse
              Serial.println("B");
              MotorB_Run(-600);
            } else if (header.indexOf("GET /L") >= 0) { // Left
              Serial.println("L");
              MotorF_Run(TURN_SPEED);
            } else if (header.indexOf("GET /M") >= 0) {
              Serial.println("M");
              MotorF_Run(0);
            } else if (header.indexOf("GET /R") >= 0) {
              Serial.println("R");
              MotorF_Run(-TURN_SPEED);
            } else {


            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 80px;");
            client.println("text-decoration: none; font-size: 12px; margin: 1px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}");
            client.println(".box {width: 150px; height: 150px; padding: 10px; border: 2px solid orange; -webkit-box-sizing: border-box; -moz-box-sizing: border-box; background: lightyellow;}");
            client.println("</style>");
            client.println("</head>");

            // Web Page Heading
            client.println("<body>");

            // client.println("<div class='box' id='left_box'>");
            // client.println("<center><h3> L </h3></center>");
            // client.println("</div>");
            // client.println("<div class='box' id='right_box'>");
            // client.println("<center><h3> R </h3></center>");
            // client.println("</div>");
            //
            // client.println("<script>");
            // client.println("window.addEventListener('load', function(){");
            // client.println("  var lbox = document.getElementById('left_box')");
            // client.println("  var rbox = document.getElementById('right_box')");
            //
            // client.println("  lbox.addEventListener('touchstart', function(e){");
            // client.println("    var xhttp = new XMLHttpRequest();");
            // client.println("    xhttp.open('GET', 'L', true);");
            // client.println("    xhttp.send();");
            // client.println("    e.preventDefault()");
            // client.println("  }, false)");
            //
            // client.println("  lbox.addEventListener('touchend', function(e){");
            // client.println("    var xhttp = new XMLHttpRequest();");
            // client.println("    xhttp.open('GET', 'M', true);");
            // client.println("    xhttp.send();");
            // client.println("    e.preventDefault()");
            // client.println("  }, false)");
            // client.println("}, false)");
            //
            // client.println("  rbox.addEventListener('touchstart', function(e){");
            // client.println("    var xhttp = new XMLHttpRequest();");
            // client.println("    xhttp.open('GET', 'R', true);");
            // client.println("    xhttp.send();");
            // client.println("    e.preventDefault()");
            // client.println("  }, false)");
            //
            // client.println("  rbox.addEventListener('touchend', function(e){");
            // client.println("    var xhttp = new XMLHttpRequest();");
            // client.println("    xhttp.open('GET', 'M', true);");
            // client.println("    xhttp.send();");
            // client.println("    e.preventDefault()");
            // client.println("  }, false)");
            // client.println("}, false)");
            //
            // client.println("</script>");


           client.println("<h2>ESP8266 Controller using Javascript and Ajax</h2>");
           // client.println("<button class=\"button\" type=\"button\" onclick=\"run('F')\">F</button>");
           // client.println("<button class=\"button\" type=\"button\" onclick=\"run('S')\">S</button>");
           // client.println("<button class=\"button\" type=\"button\" onclick=\"run('B')\">B</button>");
           // client.println("<br>");
           // client.println("<br>");
           // client.println("<br>");
           // client.println("<br>");
           // client.println("<button class=\"button\" type=\"button\" onclick=\"turn('L')\">L</button>");
           // client.println("<button class=\"button\" type=\"button\" onclick=\"turn('M')\">M</button>");
           // client.println("<button class=\"button\" type=\"button\" onclick=\"turn('R')\">R</button>");

           client.println("<div class='box' id='lbox'>");
           client.println("<center><h3>L</h3></center>");
           client.println("</div>");
           // client.println("<div class='box' id='rbox'>");
           // client.println("<center><h3>R</h3></center>");
           // client.println("</div>");

           // client.println("<p id='demo'></p>");

           client.println("<script>");
           // client.println("function run(name) {");
           // client.println("  var xhttp = new XMLHttpRequest();");
           // client.println("  xhttp.open('GET', name, true);");
           // client.println("  xhttp.send();");
           // client.println("  return false;");
           // client.println("}");

           // client.println("function turn(name) {");
           // client.println("  var xhttp = new XMLHttpRequest();");
           // client.println("  xhttp.open('GET', name, true);");
           // client.println("  xhttp.send();");
           // client.println("  sleepFor(200);");
           // client.println("  var xhttp2 = new XMLHttpRequest();");
           // client.println("  xhttp2.open('GET', 'M', true);");
           // client.println("  xhttp2.send();");
           // client.println("  return false;");
           // client.println("}");

           // client.println("function sleepFor( sleepDuration ){");
           // client.println("  var now = new Date().getTime();");
           // client.println("  while(new Date().getTime() < now + sleepDuration){ /* do nothing */ } ");
           // client.println("}");

           client.println("window.addEventListener('load', function(){");
           client.println("  var lbox = document.getElementById('left_box')");
           //client.println("  var rbox = document.getElementById('right_box')");

           client.println("  lbox.addEventListener('touchstart', function(e){");
           client.println("    var xhttp = new XMLHttpRequest();");
           client.println("    xhttp.open('GET', 'L', true);");
           client.println("    xhttp.send();");
           client.println("    e.preventDefault()");
           client.println("  }, false)");

           client.println("  lbox.addEventListener('touchend', function(e){");
           client.println("    var xhttp = new XMLHttpRequest();");
           client.println("    xhttp.open('GET', 'M', true);");
           client.println("    xhttp.send();");
           client.println("    e.preventDefault()");
           client.println("  }, false)");
           client.println("}, false)");

           // client.println("  rbox.addEventListener('touchstart', function(e){");
           // client.println("    var xhttp = new XMLHttpRequest();");
           // client.println("    xhttp.open('GET', 'R', true);");
           // client.println("    xhttp.send();");
           // client.println("    e.preventDefault()");
           // client.println("  }, false)");
           //
           // client.println("  rbox.addEventListener('touchend', function(e){");
           // client.println("    var xhttp = new XMLHttpRequest();");
           // client.println("    xhttp.open('GET', 'M', true);");
           // client.println("    xhttp.send();");
           // client.println("    e.preventDefault()");
           // client.println("  }, false)");
           // client.println("}, false)");


           client.println("</script>");



            // client.println("<h2>ESP8266 Controller using HTML</h2>");
            // client.println("<center>");
            // client.println("<a href=\"/F\"><button class=\"button\">F</button></a>");
            // client.println("<a href=\"/S\"><button class=\"button\">S</button></a>");
            // client.println("<a href=\"/B\"><button class=\"button\">B</button></a>");
            // client.println("<br");
            // client.println("<br");
            // client.println("<br");
            // client.println("<br");
            // client.println("<a href=\"/L\"><button class=\"button\">L</button></a>");
            // client.println("<a href=\"/M\"><button class=\"button\">M</button></a>");
            // client.println("<a href=\"/R\"><button class=\"button\">R</button></a>");
            // client.println("</center>");

            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
            }
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }

}

void ChangeSpeed(int spd)
{
 curSpeed = 100*spd;
}


void MotorF_Run(int spd){
  if (spd>0){
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, spd);
  }else{
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(ENB, -spd);
  }
}

void MotorB_Run(int spd){
  if (spd>0){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(ENA, spd);
  }else{
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(ENA, -spd);
  }
}
