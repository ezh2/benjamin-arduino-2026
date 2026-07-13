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
int count = 1;
void setup() {
Keyboard.begin();
pinMode(13, INPUT_PULLUP);
}

void loop() {
  if(digitalRead(13) == LOW){
    if(count == 1){
    Keyboard.press(KEY_LEFT_ARROW);
    delay(100);
    Keyboard.releaseAll();
    delay(1000);
    Keyboard.end();
    count = 0;
    }
    else if(count == 0){
    Keyboard.press(KEY_RIGHT_ARROW);
    delay(100);
    Keyboard.releaseAll();
    delay(1000);
    Keyboard.end();
    count = 1;
    }
  }
}
