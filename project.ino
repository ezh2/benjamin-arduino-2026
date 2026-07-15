const int trigPin = 6;
const int echoPin = 7;
float duration, distance;
void setup() {
  pinMode(23, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(23, HIGH);
  delay(1000);
  digitalWrite(23, LOW);
  delay(1000);

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration=pulseIn(echoPin, HIGH);
  distance=duration*0.034/2;
  Serial.print("destance");
  Serial.print(distance);
  Serial.println("cm");
  delay(500);
}
