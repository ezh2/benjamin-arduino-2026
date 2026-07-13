#include <Keypad.h>
#include <Servo.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <IRremote.hpp>

// -------------------- PINS --------------------
const int tempPin = 18;
const int fanPin1 = 3;
const int fanPin2 = 4;
const int switchPin = 2;
const int modeButtonPin = 12;
const int soundSensorPin = A0;
const int ledPin = 52;
const int doorSwitchPin = 49;
const int irPin = 36;

// RGB
const int rgbR = 6;
const int rgbG = 7;
const int rgbB = 8;
const int wcButton = 9;

// Servo
Servo myServo;

// LEDs for password
int leds[3] = {22, 24, 26};

// Password
int password[3] = {3, 1, 6};
int inputIndex = 0;

// Sound
bool ledON = false;
int lastsoundState = 0;

// Temperature
OneWire oneWire(tempPin);
DallasTemperature sensors(&oneWire);

// -------------------- KEYPAD --------------------
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {47,45,43,41};
byte colPins[COLS] = {39,37,35,33};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// -------------------- MODE --------------------
int demoMode = 1;
unsigned long lastModePress = 0;

// -------------------- SETUP --------------------
void setup() {
  Serial.begin(9600);

  pinMode(modeButtonPin, INPUT_PULLUP);
  pinMode(doorSwitchPin, INPUT_PULLUP);
  pinMode(wcButton, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  pinMode(fanPin1, OUTPUT);
  pinMode(fanPin2, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);

  pinMode(rgbR, OUTPUT);
  pinMode(rgbG, OUTPUT);
  pinMode(rgbB, OUTPUT);

  for (int i = 0; i < 3; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }

  myServo.attach(5);
  myServo.write(90); // locked

  sensors.begin();
  IrReceiver.begin(irPin, ENABLE_LED_FEEDBACK);

  Serial.println("Enter password: 3 → 1 → 6");
}

// -------------------- LOOP --------------------
void loop() {

  // MODE CHANGE BUTTON
  if (digitalRead(modeButtonPin) == LOW && millis() - lastModePress > 500) {
    demoMode++;
    if (demoMode > 4) demoMode = 1;
    Serial.print("Mode: ");
    Serial.println(demoMode);
    lastModePress = millis();
  }

  // ---------------- MODE 1 : LOCK ----------------
  if (demoMode == 1) {
    char key = keypad.getKey();
    int num = -1;
    int num2 = -1;

    if (key) {
      num = key - '0';
      Serial.print("Key: ");
      Serial.println(key);
    }

    if (IrReceiver.decode()) {
      unsigned long code = IrReceiver.decodedIRData.decodedRawData;
      if (code == 0xB847FF00) num2 = 3;
      else if (code == 0xBA45FF00) num2 = 1;
      else if (code == 0xBC43FF00) num2 = 6;
      IrReceiver.resume();
    }

    if (num != -1 || num2 != -1) {
      int input = (num != -1) ? num : num2;

      if (input == password[inputIndex]) {
        digitalWrite(leds[inputIndex], HIGH);
        inputIndex++;

        if (inputIndex == 3) {
          Serial.println("Password correct!");
          myServo.write(0);
          waitForDoorClose();
        }
      } else {
        Serial.println("Wrong password!");
        resetSystem();
      }
    }
  }

  // ---------------- MODE 2 : WC RGB ----------------
  if (demoMode == 2) {
    if (digitalRead(wcButton) == LOW) {
      analogWrite(rgbG, 125);
      analogWrite(rgbB, 0);
    } else {
      analogWrite(rgbB, 125);
      analogWrite(rgbG, 0);
    }
  }

  // ---------------- MODE 3 : SOUND LED ----------------
  if (demoMode == 3) {
    int soundState = analogRead(soundSensorPin);

    if (abs(soundState - lastsoundState) > 5) {
      ledON = !ledON;
      digitalWrite(ledPin, ledON);
      delay(200);
    }

    lastsoundState = soundState;
  }

  // ---------------- MODE 4 : TEMPERATURE ----------------
  if (demoMode == 4) {
    sensors.requestTemperatures();
    float temp = sensors.getTempCByIndex(0);

    Serial.print(temp);
    Serial.println(" °C");

    if (temp > 30 && digitalRead(switchPin) == LOW) {
      digitalWrite(fanPin1, LOW);
      digitalWrite(fanPin2, HIGH);
    } else {
      digitalWrite(fanPin1, LOW);
      digitalWrite(fanPin2, LOW);
    }
  }
}

// -------------------- FUNCTIONS --------------------
void waitForDoorClose() {
  Serial.println("Waiting for door...");
  unsigned long start = millis();

  while (digitalRead(doorSwitchPin) == HIGH) {
    if (millis() - start > 10000) break;
  }

  myServo.write(90);
  resetSystem();
}

void resetSystem() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(leds[i], LOW);
  }
  inputIndex = 0;
  Serial.println("Enter password:");
}
