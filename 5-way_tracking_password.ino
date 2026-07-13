const int sensorLeft2 = 2;
const int sensorLeft1 = 3;
const int sensorCenter = 4;
const int sensorRight1 = 5;
const int sensorRight2 = 6;
int IN1=7;
int IN2=8;
int IN3=9;
int IN4=10;
void setup() {
  Serial.begin(9600);
  pinMode(sensorLeft2, INPUT);
  pinMode(sensorLeft1, INPUT);
  pinMode(sensorCenter, INPUT);
  pinMode(sensorRight1, INPUT);
  pinMode(sensorRight2, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
}
void loop() {
  int sL2 = digitalRead(sensorLeft2);
  int sL1 = digitalRead(sensorLeft1);
  int sC = digitalRead(sensorCenter);
  int sR1 = digitalRead(sensorRight1);
  int sR2 = digitalRead(sensorRight2);

  Serial.print("Sensor State:");
  Serial.print(sL2);
  Serial.print("");
  Serial.print(sL1);
  Serial.print("");
  Serial.print(sC);
  Serial.print("");
  Serial.print(sR1);
  Serial.print("");
  Serial.print(sR2);

  if(sC == 0 && sL1 == 1 && sR1 == 1){
    Serial.println("middle");
    analogWrite(11, 50);
    analogWrite(13, 50);
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
    delay(100);
  }
  else if(sR1 == 0 && sR2 == 0 && sC == 0 && sL1 == 0 && sL2 == 0){
    Serial.println("stop");
    analogWrite(11, 50);
    analogWrite(13, 50);
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
    delay(100);  
  }
  else if(sL1 == 0){
    Serial.println("moving to left");
      analogWrite(11, 50);
      analogWrite(13, 50);
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,HIGH);
      delay(100);
      
  }
  else if(sL2 == 0){
    Serial.println("moving to left");
      analogWrite(11, 50);
      analogWrite(13, 50);
      digitalWrite(IN1,HIGH);
      digitalWrite(IN2,LOW);
      digitalWrite(IN3,LOW);
      digitalWrite(IN4,HIGH);
      delay(300);
    
  }
  else if(sR1 == 0){
    Serial.println("moving to right");
      analogWrite(11, 50);
      analogWrite(13, 50);
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,HIGH);
      digitalWrite(IN3,HIGH);
      digitalWrite(IN4,LOW);
      delay(100);
     
  }
  else if(sR2 == 0){
    Serial.println("moving to right");
      analogWrite(11, 50);
      analogWrite(13, 50);
      digitalWrite(IN1,LOW);
      digitalWrite(IN2,HIGH);
      digitalWrite(IN3,HIGH);
      digitalWrite(IN4,LOW);
      delay(300);
  
  }
  else{
    Serial.println("go in cercle");
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
    delay(100);  
  }
delay(200);
}
