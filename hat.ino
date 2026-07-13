#include <MKL_HCSR04.h>

// --- RGB LED pins ---
#define BLUE 3
#define GREEN 5
#define RED 6

// --- Ultrasonic Sensor ---
#define trig 11
#define echo 9
#define buzzer 10
MKL_HCSR04 hc(trig, echo);

// --- Buttons & LED ---
#define button1 6
#define button2 7
#define led 2

// --- Timer Input ---
#define TIMER_PIN 13

// --- Variables ---
bool on = 0;      
int TIME = 0;      

void setup() {
  // RGB LED
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);

  // Buttons & LED
  pinMode(button1, INPUT_PULLUP); 
  pinMode(button2, INPUT_PULLUP);
  pinMode(led, OUTPUT);

  // Buzzer
  pinMode(buzzer, OUTPUT);

  // Timer pin
  pinMode(TIMER_PIN, INPUT);

  Serial.begin(9600);
}

void loop() {
  // --- Part 1: RGB LED controlled by analog sensor ---
  int sensorValue = analogRead(A0);
  Serial.print("Analog: ");
  Serial.println(sensorValue);

  if (sensorValue < 120) {        // Low range
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
  } 
  else if (sensorValue < 700) {  // Mid range
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, HIGH);
  } 
  else {                         // High range
    digitalWrite(RED, LOW);
NEW SKETCH

    digitalWrite(GREEN, HIGH);
  }

  // --- Part 2: Ultrasonic Sensor with Buzzer ---
  float distance = hc.dist();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  bool ultrasonicBuzz = false;
  if (distance > 0 && distance <= 40) {
    ultrasonicBuzz = true;
  }

  // --- Part 3: Button 1 toggles LED ---
  if (digitalRead(button1) == LOW) { 
    Serial.println(on);
    on = !on;
    delay(300);  // debounce
  }
  digitalWrite(led, on ? HIGH : LOW);

  // --- Part 4: Button 2 controls buzzer ---
  bool buttonBuzz = (digitalRead(button2) == LOW);

  // --- Part 5: Timer on pin 13 ---
  bool timerBuzz = false;
  if (digitalRead(TIMER_PIN) == LOW) {
    TIME++;
    delay(1000);  // count in seconds
    Serial.print("TIME: ");
    Serial.println(TIME);
    if (TIME > 4) {
      timerBuzz = true;
      Serial.println("fall");
    }
  } else {
    TIME = 0;
    timerBuzz = false;
    Serial.println("reset");
  }

  // --- Final Buzzer Control (any source can turn it ON) ---
  if (ultrasonicBuzz || buttonBuzz || timerBuzz) {

  } else {
    digitalWrite(buzzer, LOW);
  }

  delay(100);
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    