int buzzer = 12;

void setup() {
  // put your setup code here, to run once:
  pinMode(buzzer,OUTPUT);
  Serial.begin(9600);
}
void spaceGun(int maximum){
  for(int i = 0; i <maximum; i++){
    digitalWrite(buzzer,HIGH);
    delayMicroseconds(i);
    digitalWrite(buzzer,LOW);
    delayMicroseconds(i);
  }
}

void randSound(int maximum){
  tone(buzzer,random(maximum,10*maximum));
  delay(maximum);
}

void fibonacci(int maximum){
  long fib = 1;
  long fib1 = 1;
  long fib2 = 2;
  for( int i = 0; i <maximum; i++){
    Serial.println(fib);
    fib = fib1+fib2;
    fib1 = fib2;
    fib2 = fib;
    tone(buzzer,fib);
    delay(200);
  }
}



void gun2(){
  for(int i = 0; i <2000; i=i+10){
    digitalWrite(buzzer,HIGH);
    delayMicroseconds(i);
    digitalWrite(buzzer,LOW);
    delayMicroseconds(i);
  }
}

void alarm(){
  for(int i = 0; i <1500; i=i+10){
    tone(buzzer,i);
    delayMicroseconds(i);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  //gun2();
  //spaceGun(300);
  //randSound(300);
  //fibonacci(20);
  alarm();

  //tone(buzzer,1600);
  //noTone(buzzer);
}
