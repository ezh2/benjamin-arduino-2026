const int trigPin = 5;
const int echoPin = 18;
float duration, distance;
void setup() {
  pinMode(23, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(17,INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration=pulseIn(echoPin, HIGH);
  distance=duration*0.034/2;
  Serial.print("distance");
  Serial.print(distance);
  Serial.println("cm");
  delay(500);
  if(distance<=20){
    digitalWrite(23, HIGH);
    delay(1000);
    digitalWrite(23, LOW);
    delay(3000);
  }
    if(digitalRead(17)==LOW){
      digitalWrite(23, HIGH);
      delay(1000);
    }
    else{
      digitalWrite(23, LOW);
    }
  }

}
