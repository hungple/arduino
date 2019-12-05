#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

int curSpeed = 200;

int ENA = 5;
int IN1 = 3;
int IN2 = 4;

int ENB = 8;
int IN3 = 6;
int IN4 = 7;


// int back_led = 13;
// int front_led = 12;

void setup() {
  // initialize Serial module
  Serial.begin(9600); // Default connection rate for my BT module

  // Right motor
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  
  // Left motor
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // back and front leds 
  // pinMode(back_led, OUTPUT);
  // pinMode(front_led, OUTPUT);
}

void loop() {
 if(Serial.available() > 0){
   char letter = Serial.read();
   Serial.println(letter);

   if(letter == 'f'){
     Forward();
   }
   else if(letter == 'b'){
     Backward();
   }
   else if(letter == 'r' || letter == 'i' || letter == 'j'){
     TurnRight();
   }
   else if(letter == 'l' || letter == 'g' || letter == 'h'){
     TurnLeft();
   }
   else if(letter == '1'){
     ChangeSpeed(1);
   }
   else if(letter == '2'){
     ChangeSpeed(2);
   }

   else if(letter == '3'){
     ChangeSpeed(3);
   }


   else if(letter == '4'){
     ChangeSpeed(4);
   }


   else if(letter == '5'){
     ChangeSpeed(5);
   }


   else if(letter == '6'){
     ChangeSpeed(6);
   }


   else if(letter == '7'){
     ChangeSpeed(7);
   }


   else if(letter == '8'){
     ChangeSpeed(8);
   }


   else if(letter == '9'){
     ChangeSpeed(9);
   }

   else if(letter == 's'){
     Stop();
   }

   else if(letter == 'W'){
     digitalWrite(13, HIGH);
   }

   else if(letter == 'w'){
     digitalWrite(13, LOW);
   }

   else if(letter == 'U'){
     digitalWrite(12, HIGH);
   }

   else if(letter == 'u'){
     digitalWrite(12, LOW);
   }
 }
}

void Forward()
{
 MotorR_Run(curSpeed);
 MotorL_Run(curSpeed);
}

void Backward()
{
 MotorR_Run(-curSpeed);
 MotorL_Run(-curSpeed);
}

void TurnLeft()
{
 MotorL_Run(-500);
 MotorR_Run(500);
}

void TurnRight()
{
 MotorL_Run(500);
 MotorR_Run(-500);
}

void Stop()
{
 MotorR_Run(0);
 MotorL_Run(0);
}

void ChangeSpeed(int spd)
{
 curSpeed = 100*spd;
}


void MotorR_Run(int spd){
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

void MotorL_Run(int spd){
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
