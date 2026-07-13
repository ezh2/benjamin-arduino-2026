#include <Keypad.h>
#include <Servo.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <Key.h>

const int tempPin = 18;
const int fanPin1 = 3;
const int fanPin2 = 4;
const int switchPin = 2;
const int buttonPin = 12;

OneWire oneWire(tempPin);
DallasTemperature sensors(&oneWire);

const int soundSensorPin = A0;
const int ledPin = 52;
bool ledON = 0;
int lastsoundState=0;
// Servo
Servo myServo;

// LEDs
int leds[3] = {22, 24, 26};

// Password
int password[3] = {3, 1, 6};
int inputIndex = 0;

// Magnetic switch
int doorSwitchPin = 49;

// Keypad setup
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {47, 45, 43, 41};
byte colPins[COLS] = {39, 37, 35, 33};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int demoMode = 1;
#include <IRremote.hpp>
const int irPin=36;

void setup() {
  pinMode(12, INPUT_PULLUP);
  Serial.begin(9600);

  for (int i = 0; i < 3; i++) {
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], LOW);
  }

  // Servo setup
  myServo.attach(5);
  myServo.write(90); // Start locked

  // Door switch setup
  pinMode(doorSwitchPin, INPUT_PULLUP);

  Serial.println("Enter password: 3 → 1 → 6");

  pinMode(9, INPUT_PULLUP);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);

  pinMode(fanPin1, OUTPUT);
  pinMode(fanPin2, OUTPUT);
  pinMode(switchPin, INPUT_PULLUP);

  sensors.begin();

  pinMode(ledPin, OUTPUT);
  IrReceiver.begin(irPin,ENABLE_LED_FEEDBACK);
}

void loop() {
  
//keypade LOCK
  if (digitalRead(12) == 0) {
    demoMode++;
    delay(1000);
    if (demoMode > 4) {
      demoMode = 1;
    }
    Serial.print("Mode: ");
    Serial.println(demoMode);
  }

  if (demoMode == 1) {
    char key = keypad.getKey();
  unsigned long code;
  int num2=0;
    if (key || IrReceiver.decode()) {
 code=IrReceiver.decodedIRData.decodedRawData;
   if(code==0xB847FF00){
 Serial.println("3");
num2=3;
delay(500);
  }
  else if(code==0xBA45FF00){
     Serial.println("1");
     num2=1;
     delay(500);
  }
  else if(code==0xBC43FF00){
     Serial.println("6");
     num2=6;
     delay(500);
  }
if(key){
      Serial.print("Key pressed: ");
      Serial.println(key);
  }
        int num = key - '0';

        if (num == password[inputIndex] || num2==password[inputIndex]) {
          digitalWrite(leds[inputIndex], HIGH);
          inputIndex++;

          if (inputIndex == 3) {
            Serial.println("Password correct! Unlocking door...");
            myServo.write(0); // Unlock
            delay(4000);
            waitForDoorClose();
          }
        } 
        else {
          Serial.println("Wrong number! Resetting...");
          resetSystem();
        }
    }
     IrReceiver.resume();
  }
// WC RGB
  if (demoMode == 2) {
    if (digitalRead(9) == LOW) {
      analogWrite(7, 125);
      analogWrite(8, 0);
    } else {
      analogWrite(8, 125);
      analogWrite(7, 0);
    }
    delay(100);
  }
//sound control LED
  if (demoMode == 3) {
    
    int soundState = analogRead(soundSensorPin);
    Serial.println(soundState);

    if (soundState > lastsoundState+5) {
      ledON = !ledON;

      if (ledON == 4) {
        Serial.println("LED ON");
        digitalWrite(ledPin, HIGH);
      } else if (ledON == 0) {
        digitalWrite(ledPin, LOW);
        Serial.println("LED OFF");
      }

      delay(200);
    }

    lastsoundState = soundState;
  }

//temperature
  if (demoMode == 4) {
      sensors.requestTemperatures();
      float temp = sensors.getTempCByIndex(0);
      Serial.print(temp);
      Serial.println("°C");

      if (temp > 28 && digitalRead(2) == 0) {
        digitalWrite(3, LOW);
        digitalWrite(4, HIGH);
        // delay(10);
      } else {
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        // delay(10);
      }
    
  }
}

void waitForDoorClose() {
  Serial.println(" Waiting for door to close...");
  while (digitalRead(doorSwitchPin) == HIGH) {
    // Waiting (HIGH means door open)
  }
  Serial.println("Door closed. Locking...");
  delay(500);
  myServo.write(90); // Lock back at 90°
  resetSystem();
}

void resetSystem() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(leds[i], LOW);
  }
  inputIndex = 0;
  Serial.println("Enter first number:");
}
//pleas don't chang any thing :)