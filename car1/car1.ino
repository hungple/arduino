 
#include <Makeblock.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

MeDCMotor MotorF(M1);  
MeDCMotor MotorB(M2);
MeInfraredReceiver infraredReceiverDecode(PORT_6);
int moveSpeed = 190;
boolean leftflag,rightflag;
int minSpeed = 55;
int factor = 23;

int ledPin = 13;
int delayTime = 200;
int preDirection = 0; //0: forward - 1:backward
//int flag = 0; 
 
void setup() {
 pinMode(ledPin, OUTPUT);
 digitalWrite(ledPin, LOW);
 
 Serial.begin(9600); // Default connection rate for my BT module
}
 
void loop() {
  if(Serial.available() > 0){
    char letter = Serial.read();
    Serial.println(letter);
  
    if(letter == 'f'){
      Forward();
      preDirection = 0;
    }
    else if(letter == 'b'){
      Backward();
      preDirection = 1;
    }
    else if(letter == 'r'){
      TurnRight(preDirection);
    }
    else if(letter == 'l'){
      TurnLeft(preDirection);
    }
    else if(letter == 's'){
      Stop();
    }
  }
}

void Forward()
{
  MotorB.run(moveSpeed);
  delay(delayTime);
  MotorB.run(0);
}
void Backward()
{
  MotorB.run(-moveSpeed);
  delay(delayTime);
  MotorB.run(0);
}
void TurnLeft(int preDirection)
{
  MotorF.run(-moveSpeed);
  if(preDirection == 0){
    MotorB.run(moveSpeed);
  }
  else{
    MotorB.run(-moveSpeed);
  }
  delay(delayTime);
  MotorF.run(0);
  MotorB.run(0);
}
void TurnRight(int preDirection)
{
  MotorF.run(moveSpeed);
  if(preDirection == 0){
    MotorB.run(moveSpeed);
  }
  else{
    MotorB.run(-moveSpeed);
  }
  delay(delayTime);
  MotorF.run(0);
  MotorB.run(0);
}
void Stop()
{
  MotorB.run(0);
}
void ChangeSpeed(int spd)
{
  moveSpeed = spd;
}
