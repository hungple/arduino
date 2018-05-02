/*************************************************************************
* File Name          : Makeblock_BT_Controller.ino
* Author             : Miguel SC
* Updated            : Miguel SC
* Version            : V2.0
* Date               : 20/08/2014
* Description        : 
**************************************************************************/
#include <Makeblock.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

MeDCMotor MotorL(M1);  
MeDCMotor MotorR(M2);
MeDCMotor motorCrane_1(PORT_1);
MeDCMotor motorCrane_2(PORT_2);
MeUltrasonicSensor UltrasonicSensor(PORT_8);
MeBluetooth bluetooth(PORT_3);


int distance = 0;
int timer = 25;
int craneSpeed = 200;
int moveSpeed = 0;


void setup(){
    Serial.begin(9600);
    bluetooth.begin(9600);
    distance = UltrasonicSensor.distanceCm();
}



void loop(){
  
    char inDat;
    char outDat;
    timer--;
    if (timer==0){
      int timer = 15;
      if (distance != UltrasonicSensor.distanceCm()){
          distance = UltrasonicSensor.distanceCm();
          if (distance == 0)
            bluetooth.print("--");
          else
            bluetooth.print(distance);
          delay(40);
      }
    }
    
    
    if(bluetooth.available()){
        
        inDat   = bluetooth.read();
        int aux = 0;     
        switch(inDat){
          case 'U': 
               Forward();
               break;
          case 'D':
               Backward();
               break;
          case 'R':
               TurnRight();
               break;
          case 'L':
               TurnLeft();
               break;
          case 'S':
               Stop();
               break;
          case 'H':
               upCrane();
               break;
          case 'B':
               downCrane();
               break;
          case '0':
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9':
               aux = inDat-'0';
               ChangeSpeed(50*aux);
               break;
          default:
               Stop();
               break;
               
        }
           
    }
}

void upCrane()
{
  motorCrane_1.run(craneSpeed);
}

void downCrane()
{
  motorCrane_1.run(-craneSpeed);
} 

void Forward()
{
 
  MotorL.run(moveSpeed);
  MotorR.run(moveSpeed);
}
void Backward()
{
  MotorL.run(-moveSpeed);
  MotorR.run(-moveSpeed);
}
void TurnLeft()
{
  MotorL.run(-moveSpeed);
  MotorR.run(moveSpeed);
}

void TurnRight()
{
  MotorL.run(moveSpeed);
  MotorR.run(-moveSpeed);
}

void Stop()
{
  MotorL.run(0);
  MotorR.run(0);
  motorCrane_1.run(0);
  motorCrane_2.run(0);
}
void ChangeSpeed(int spd)
{
  moveSpeed = spd;
}
