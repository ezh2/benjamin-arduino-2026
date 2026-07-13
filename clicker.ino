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
#include <Mouse.h>
const int buttonPin = 13;
int count = 0;
void setup() {
pinMode(buttonPin, INPUT_PULLUP);
Serial.begin(9600);
Mouse.begin();
}

void loop() {
  if(digitalRead(buttonPin) == LOW){
     Serial.println(count);
     while(count<10000){
      delay(1);
          count++;
 Mouse.click();
    }
  }
}
