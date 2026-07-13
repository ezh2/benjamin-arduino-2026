int sequence[6], ans[6];
void printout(int i){
   for (int j=0;j<i;j++){
      Serial.print(ans[j]);
  	}
  Serial.println();
}
#define redLED 3
#define blueLED 2
#define yellowLED 9
#define greenLED 8

#define redbutton 4
#define bluebutton 5
#define yellowbutton 6
#define greenbutton 7

void allLightOff(){
	digitalWrite(redLED, LOW);
  digitalWrite(blueLED, LOW);
  digitalWrite(greenLED, LOW);
  digitalWrite(yellowLED, LOW);
}

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(A0));
  
  pinMode(blueLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  
  pinMode(redbutton,INPUT);
  pinMode(bluebutton,INPUT);
  pinMode(yellowbutton,INPUT);
  pinMode(greenbutton,INPUT);
  
  digitalWrite(redLED, HIGH);
  digitalWrite(blueLED, HIGH);
  digitalWrite(greenLED, HIGH);
  digitalWrite(yellowLED, HIGH);
  delay(2000);
  allLightOff();
  
}
int seqLen=0;

void loop() {
  
  if (seqLen < 6){
  	int randNum = random(1, 5);
    sequence[seqLen]=randNum;

    //generate random number sequence & display
    for (int i=0;i<seqLen;i++){
      Serial.print(sequence[i]);
      Serial.print(" ");
      if(sequence[i]==1){
      	digitalWrite(redLED, HIGH);
        delay(500);
        digitalWrite(redLED, LOW);
      }
      else if(sequence[i]==2){
        digitalWrite(blueLED, HIGH);
        delay(500);
        digitalWrite(blueLED, LOW);
      }
      else if(sequence[i]==3){
        digitalWrite(yellowLED, HIGH);
        delay(500);
        digitalWrite(yellowLED, LOW);
      }
      else if(sequence[i]==4){
        digitalWrite(greenLED, HIGH);
        delay(500);
        digitalWrite(greenLED, LOW);
      }
      allLightOff();
      delay(500);
    }
    Serial.println("");
    
    //user input & check ans
    int j=0;
    Serial.print("Inputing: ");
    while(j<seqLen){
      int buttonIn=0;
      //wait for button input
      while(1){
        if (digitalRead(redbutton)==1){
          buttonIn=1;
          Serial.print("1 ");
          
          digitalWrite(redLED, HIGH);
          delay(500);
          digitalWrite(redLED, LOW);
          
          while (digitalRead(redbutton) == HIGH) {};
		      delay(20);  
          break;
        }
        else if (digitalRead(bluebutton)==1){
          buttonIn=2;
          Serial.print("2 ");
          
          digitalWrite(blueLED, HIGH);
          delay(500);
          digitalWrite(blueLED, LOW);
          
          while (digitalRead(bluebutton) == HIGH) {};
		      delay(20);
          break;
        }
        else if (digitalRead(yellowbutton)==1){
          buttonIn=3;
          Serial.print("3 ");
     
          digitalWrite(yellowLED, HIGH);
          delay(500);
          digitalWrite(yellowLED, LOW);
          
          
          while (digitalRead(yellowbutton) == HIGH) {};
		      delay(20);
          break;
        }
        else if (digitalRead(greenbutton)==1){
          buttonIn=4;
          Serial.print("4 ");
          digitalWrite(greenLED, HIGH);
          delay(500);
          digitalWrite(greenLED, LOW);
          
          while (digitalRead(greenbutton) == HIGH) {};
		      delay(20);
          break;
        }
      } 
      
      if(sequence[j]==buttonIn) j++;
      else {
        Serial.print("YOU FAILED");
        while(1){}
      }
    }
   	if (j==5){
    	digitalWrite(redLED, HIGH);
  		digitalWrite(blueLED, HIGH);
  		digitalWrite(greenLED, HIGH);
  		digitalWrite(yellowLED, HIGH);
      	Serial.print("YOU WIN");
      	while(1){}
    }
    Serial.println("");
    delay(2000);
    seqLen++;
  }
  

  
}
