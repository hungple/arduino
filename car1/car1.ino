 
#include <Makeblock.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

MeDCMotor MotorF(M1);  
MeDCMotor MotorB(M2);
MeInfraredReceiver infraredReceiverDecode(PORT_6);
int moveSpeed = 300;
//boolean leftflag,rightflag;
//int minSpeed = 55;
//int factor = 23;

int ledPin = 13;
//int delayTime = 300;
 
void setup() {
  // initialize Serial module
  Serial.begin(9600); // Default connection rate for my BT module

  // set up the led on pin 13
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}
 
void loop() {
  if(Serial.available() > 0){
    char letter = Serial.read();
    Serial.println(letter);
  
    if(letter == 'F'){
      Forward();
    }
    else if(letter == 'B'){
      Backward();
    }
    else if(letter == 'R' || letter == 'I' || letter == 'J'){
      TurnRight();
    }
    else if(letter == 'L' || letter == 'G' || letter == 'H'){
      TurnLeft();
    }
    else if(letter == 'S'){
      Stop();
    }
  }
}

void Forward()
{
  MotorB.run(moveSpeed);
}

void Backward()
{
  MotorB.run(-moveSpeed);
}

void TurnLeft()
{
  MotorF.run(-100);
}

void TurnRight()
{
  MotorF.run(100);
}

void Stop()
{
  MotorB.run(0);
  MotorF.run(0);
}

void ChangeSpeed(int spd)
{
  moveSpeed = spd;
}
