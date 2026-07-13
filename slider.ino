#include <Keyboard.h>
#include <KeyboardLayout.h>
#include <Keyboard_da_DK.h>
#include <Keyboard_de_DE.h>
#include <Keyboard_es_ES.h>
#include <Keyboard_fr_FR.h>
#include <Keyboard_hu_HU.h>
#include <Keyboard_it_IT.h>
#include <Keyboard_pt_PT.h>
#include <Keyboard_sv_SE.h>

const int sensorLeft2 = 2;
const int sensorLeft1 = 3;
const int sensorCenter = 4;
const int sensorRight1 = 5;
const int sensorRight2 = 6;
int pev;
int now;
void setup() {
  pinMode(sensorLeft2, INPUT);
  pinMode(sensorLeft1, INPUT);
  pinMode(sensorCenter, INPUT);
  pinMode(sensorRight1, INPUT);
  pinMode(sensorRight2, INPUT);
  Serial.begin(2000000);
  Keyboard.begin();
}

void loop() {
  int sL2 = digitalRead(sensorLeft2);
  int sL1 = digitalRead(sensorLeft1);
  int sC = digitalRead(sensorCenter);
  int sR1 = digitalRead(sensorRight1);
  int sR2 = digitalRead(sensorRight2);
if(pev!=0 && now!=0 && now>pev){
  Serial.println("left_to_right");
  Keyboard.press(KEY_RIGHT_ARROW);
  Keyboard.releaseAll();
  pev = 0;
  now = 0;
  delay(1000);
}
else if(pev!=0 && now!=0 &&pev>now){
  Serial.println("right_to_left");
  Keyboard.press(KEY_LEFT_ARROW);
  Keyboard.releaseAll();
  pev = 0;
  now = 0;
  delay(1000);
}
    else if(sL2){
      pev=now;
      //if(pev==0) pev=1;
      now=1;
    }
    else if(sL1){
      pev=now;
      //if(pev==0) pev=2;
      now=2;
    }
    else if(sC){
      pev=now;
      //if(pev==0) pev=3;
      now=3;
    }
    else if(sR1){
      pev=now;
      //if(pev==0) pev=4;
      now=4;
    }
    else if(sR2){
      pev=now;
      //if(pev==0) pev=5;
      now=5;
    }
    Serial.print(pev);
    Serial.println(now);
}
