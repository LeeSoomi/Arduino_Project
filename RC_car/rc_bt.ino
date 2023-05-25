#include <SoftwareSerial.h>

int bluetoothTx = 2;
int bluetoothRx = 3;

int sp = 200 ;

int ENA1 = 10 ;
int IN1 =  9 ;
int IN2 = 8 ;

int IN3 =  7;
int IN4 = 6 ;
int ENA2 = 5 ;
//char cmd ;
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup() { //Setup usb serial connection to computer
 Serial.begin(9600); //Setup Bluetooth serial connecti/on to android
 delay(100);
 bluetooth.begin(9600);
 pinMode(ENA1, OUTPUT) ;
 pinMode(IN1, OUTPUT) ; 
 pinMode(IN2, OUTPUT) ; 
 pinMode(ENA2, OUTPUT) ;
 pinMode(IN3, OUTPUT) ; 
 pinMode(IN4, OUTPUT) ;  
}
void forward(){
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,LOW);
   analogWrite(ENA1,sp);
   digitalWrite(IN3,HIGH);
   digitalWrite(IN4,LOW);
   analogWrite(ENA2,sp); 
}
void backward(){
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,HIGH);
   analogWrite(ENA1,sp);
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,HIGH);
   analogWrite(ENA2,sp); 
}

void right(){
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,HIGH);
   analogWrite(ENA1,sp);
   digitalWrite(IN3,HIGH);
   digitalWrite(IN4,LOW);
   analogWrite(ENA2,sp); 
}

void left(){
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,LOW);
   analogWrite(ENA1,sp);
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,HIGH);
   analogWrite(ENA2,sp); 
}

void st(){
   analogWrite(ENA1,0);
   analogWrite(ENA2,0);
}

void loop() {

  if(bluetooth.available()) {
  char cmd = (char)bluetooth.read();
  Serial.println(cmd);
  if(cmd == 'g') {
   forward();
  }
  else if(cmd == 'b') {
   backward() ;
  }
  else if(cmd == 'l') {
   left();
  }
  else if(cmd == 'r') {
   right() ;
  } 
  else {
   st() ;
  }
 }
}
