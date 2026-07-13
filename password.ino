#include <Servo.h>
 Servo lock;
 const int sensorLeft2 = 2;
const int sensorLeft1 = 3;
const int sensorCenter = 4;
const int sensorRight1 = 5;
const int sensorRight2 = 6;
int state = 0;
void setup() {
  Serial.begin(9600);
  lock.attach(9);
  pinMode(sensorLeft2, INPUT);
  pinMode(sensorLeft1, INPUT);
  pinMode(sensorCenter, INPUT);
  pinMode(sensorRight1, INPUT);
  pinMode(sensorRight2, INPUT);
  pinMode(7,OUTPUT);
}

void loop() {
  int sL2 = digitalRead(sensorLeft2);
  int sL1 = digitalRead(sensorLeft1);
  int sC = digitalRead(sensorCenter);
  int sR1 = digitalRead(sensorRight1);
  int sR2 = digitalRead(sensorRight2);
  
  Serial.println(state);
  lock.write(90);
  if(state == 0){
    if(sC == 1 && sL2 == 1 && sL1 ==0 && sR1 ==0 && sR2==0){
      state=1;
      Serial.println(state); 
             digitalWrite(7, HIGH);
          delay(100);
          digitalWrite(7, LOW);
          delay(100);
          digitalWrite(7, HIGH);
          delay(100);
          digitalWrite(7, LOW);
          delay(100);
      while(sC == 1 || sL2 == 1){
        Serial.println("Wait for release");
          sL2 = digitalRead(sensorLeft2);
        sL1 = digitalRead(sensorLeft1);
       sC = digitalRead(sensorCenter);
        sR1 = digitalRead(sensorRight1);
       sR2 = digitalRead(sensorRight2);
        delay(50);

      }
      }
  }
    if(state == 1){
      if(sC == 1 || sL2 == 1 || sL1 == 1){
        Serial.print("wrong");
          digitalWrite(7, HIGH);
          delay(1000);
            digitalWrite(7, LOW);
            state=0;
      }
          if(sC == 0 && sL2 == 0 && sL1 ==0 && sR1 ==1 && sR2==1){
      state=2;
      Serial.println(state);
          digitalWrite(7, HIGH);
          delay(100);
          digitalWrite(7, LOW);
          delay(100);
          digitalWrite(7, HIGH);
          delay(100);
          digitalWrite(7, LOW);
          delay(100);
      while(sR2 == 1 || sR1 == 1){
        Serial.println("Wait for release");
          sL2 = digitalRead(sensorLeft2);
        sL1 = digitalRead(sensorLeft1);
       sC = digitalRead(sensorCenter);
        sR1 = digitalRead(sensorRight1);
       sR2 = digitalRead(sensorRight2);
        delay(50);
        }
      }
   }
   if(state == 2){
      if(sC == 1 || sR1 == 1 || sL1 == 1){
        Serial.print("wrong");
        digitalWrite(7, HIGH);
        delay(1000);
        digitalWrite(7, LOW);
        state=0;
      }
      if(sR1 == 0 && sR2 == 1 && sC == 0 && sL1 == 0 && sL2 == 1){
      digitalWrite(7, HIGH);
          delay(100);
          digitalWrite(7, LOW);
          delay(100);
          digitalWrite(7, HIGH);
          delay(100);
          digitalWrite(7, LOW);
          delay(100);
       lock.write(0);
       delay(2000);
       digitalWrite(7, HIGH);
       delay(500);
       digitalWrite(7, LOW);
       delay(500);
       digitalWrite(7, HIGH);
       delay(500);
       digitalWrite(7, LOW);
       delay(500);
       digitalWrite(7, HIGH);
       lock.write(90); 
       delay(1000);
       digitalWrite(7, LOW);
       delay(500);
       state=0;
      }
   }
  }
