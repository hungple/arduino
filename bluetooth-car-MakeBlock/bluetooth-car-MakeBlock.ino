 
#include <Makeblock.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Wire.h>

MeDCMotor MotorF(M1);  
MeDCMotor MotorB(M2);
//MeInfraredReceiver infraredReceiverDecode(PORT_6);
int curSpeed = 100;

//boolean leftflag,rightflag;
//int minSpeed = 55;
//int factor = 23;

int ledPin = 13;
//int delayTime = 300;
 
void setup() {
  // initialize Serial module
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  Serial.begin(9600); // Default connection rate for my BT module

  // set up the led on pin 13
  //pinMode(ledPin, OUTPUT);
  //digitalWrite(ledPin, LOW);
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
           
    else if(letter == 'S'){
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
  MotorB.run(curSpeed);
}

void Backward()
{
  MotorB.run(-curSpeed);
}

void TurnLeft()
{
  MotorF.run(-1000);
}

void TurnRight()
{
  MotorF.run(1000);
}

void Stop()
{
  MotorB.run(0);
  MotorF.run(0);
}

void ChangeSpeed(int spd)
{
  curSpeed = 100*spd;
}
