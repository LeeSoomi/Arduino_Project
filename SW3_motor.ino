
const int switchPin1 = 2; // the number of the switch pin
const int switchPin2 = 3; // the number of the switch pin
const int switchPin3 = 4; // the number of the switch pin
const int motorPin = 9; // the number of the motor pin


int switchState1 = LOW ;
int switchState2 = LOW ; 
int switchState3 = LOW ;  

int POW_LEVEL = 0 ;

void setup() {
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  pinMode(switchPin1, INPUT);
  pinMode(switchPin2, INPUT);
  pinMode(switchPin3, INPUT); 
}

void loop() {

  switchState1 = digitalRead(switchPin1);
  if (switchState1 == HIGH) {
    POW_LEVEL = 1 ;
    }

  switchState2 = digitalRead(switchPin2);  
  if (switchState2 == HIGH) {
     POW_LEVEL = 2 ;
    }

  switchState3 = digitalRead(switchPin3); 
  if (switchState3 == HIGH) {
     POW_LEVEL = 0 ;
    }
  Serial.println(POW_LEVEL);
  
  if (POW_LEVEL == 1){   
   analogWrite(motorPin, 100);}
  else if (POW_LEVEL == 2){   
   analogWrite(motorPin, 200);} 
  else if (POW_LEVEL == 0){   
   analogWrite(motorPin, 0);}   
}
