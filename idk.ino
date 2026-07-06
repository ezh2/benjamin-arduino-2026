#include <Wire.h>;
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#include <Key.h>
#include <Keypad.h>

int player_1;
int player_2;
int state = 0;
int dice_1;
int dice_2;
String count="";
int count_int;
bool once=0;
const int ROW_NUM = 4;
const int COLUMN_NUM = 4;

char keys[ROW_NUM][COLUMN_NUM] =
{
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

byte pin_rows[ROW_NUM] = {6, 7, 8, 9};
byte pin_column[COLUMN_NUM] = {10, 11, 12, 13};

Keypad keypad = Keypad(
    makeKeymap(keys),
    pin_rows,
    pin_column,
    ROW_NUM,
    COLUMN_NUM
);
int IN1=5;
int IN2=4;
int IN3=3;
int IN4=2;
void setup(){
    lcd.init();
    lcd.backlight();
    Serial.begin(9600);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    pinMode(1, INPUT_PULLUP);

    digitalWrite(IN1,LOW);
       digitalWrite(IN2,LOW);
       digitalWrite(IN3,LOW);
       digitalWrite(IN4,LOW); 

    delay(2000);
    randomSeed(analogRead(A0));
}

void loop(){
    if (state == 0){
        char key = keypad.getKey();
        //Serial.println(key);
        if(key == 'C'){
            lcd.clear();
            
          lcd.print("insert card...");
          while(analogRead(A0)>900){
          }
            while(analogRead(A0)<300){
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("p1");
                lcd.setCursor(0,1);
                lcd.print(player_1);
                delay(3000);
            }
            while(analogRead(A0)>500&&analogRead(A0)<800){
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("p2");
                lcd.setCursor(0,1);
                lcd.print(player_2);
                delay(3000);
            }
            lcd.clear();
          }
    
       lcd.setCursor(0,0);
       lcd.print("press button");
       if(digitalRead(1) == 0){
       digitalWrite(IN1,HIGH);
       digitalWrite(IN2,LOW);
       digitalWrite(IN3,HIGH);
       digitalWrite(IN4,LOW);
       delay(1000);
       digitalWrite(IN1,LOW);
       digitalWrite(IN2,LOW);
       digitalWrite(IN3,LOW);
       digitalWrite(IN4,LOW); 
       once =0;
       state=1;
       }
    }

    if (state == 1){
         // Serial.println("state_1");
        char key = keypad.getKey();
        if(once==0){
            lcd.clear();
        lcd.setCursor(0, 1);
        lcd.print("A:add B:deduct");
        lcd.setCursor(0, 0);
        once = 1;
        }

        if (key == '1' || key == '2' || key == '3' ||
            key == '4' || key == '5' || key == '6' ||
            key == '7' || key == '8' || key == '9' ||
            key =='0')
        {
             lcd.print(key);
             count+= key;
        }

        if (key == 'A')
        {
            if(count.toInt()==0 || count==""){
                lcd.clear();
                lcd.print("error");
                lcd.setCursor(0, 1);
                lcd.print("A:add B:deduct");
                delay(3000);
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("A:add B:deduct");
                lcd.setCursor(0, 0);
            }
            else{
            lcd.setCursor(0, 0);
            lcd.print('+');
           // lcd.print();
            lcd.print("add");
            lcd.print(count);
            lcd.setCursor(0, 1);
            lcd.print("insert card...");
            state = 2;
            count_int=count.toInt();
            }
        }

        if (key == 'B')
        {
            if(count.toInt()==0 || count==""){
                lcd.clear();
                lcd.print("error");
                lcd.setCursor(0, 1);
                lcd.print("A:add B:deduct");
                delay(3000);
                lcd.clear();
                lcd.setCursor(0, 1);
                lcd.print("A:add B:deduct");
                lcd.setCursor(0, 0);
            }
            else{
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print('-');
            //lcd.print();
            lcd.print("deduct");
            lcd.print(count);
            lcd.setCursor(0, 1);
            lcd.print("insert card...");
            state = 2;
            count_int=count.toInt()*-1;
            }
        }

    }
    
    if (state==2){
        delay(1000);
         // Serial.println("state_2");
        if(analogRead(A0)>1000){
            //Serial.println("there_is_nothing");
            delay(500);
        }
        else if(analogRead(A0)<300){
            player_1+= count_int;
            lcd.clear();
            lcd.print("player_1");
            lcd.setCursor(0, 1);
            lcd.print("#:ok *:cancel");
            state=3;
        }
        else if(analogRead(A0)>500&&analogRead(A0)<800){
            player_2+= count_int;
            lcd.clear();
            lcd.print("player_2");
            lcd.setCursor(0, 1);
            lcd.print("#:ok *:cancel");
            state=3;
        }
    }
    if(state==3){
         // Serial.println("state_3");
        char key = keypad.getKey();
        if(key == '#'){
            lcd.clear();
            lcd.print("confirm");
            delay(2000);
            state=4;
        }
        if(key == '*'){
            lcd.clear();
            lcd.print("cancel");
            delay(2000);
            once=0;
            state=1;
        }
    }
    if(state==4){
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("P2:");
    lcd.setCursor(3, 1);
    lcd.print(player_2);
    lcd.setCursor(0, 0);
    lcd.print("P1:");
    lcd.setCursor(3, 0);
    lcd.print(player_1);
    delay(6000);
    lcd.clear();
    if(player_1||player_2<0){
            if(player_1<0){
                lcd.print("P1 lost");
                delay(3000);
                lcd.clear();
            }
            if(player_2<0){
                lcd.print("P2 lost");
                delay(3000);
                lcd.clear();
            }
        lcd.print("game over");
        delay(3000);
        lcd.clear();
        player_1 = 0;
        player_2 = 0;
        state=0;  
    }
    count="";
    state=0;    
    }
}