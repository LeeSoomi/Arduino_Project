// delay 사용으로 동작 흐름이 원활하지 못함

#include "thingProperties.h"


int pir_pin = 4; //D2
int Green_Led = 13; //D7, Green
int Red_Led = 2 ;  //D4,  Red
int Gas_pin = A0 ;

void setup() {  
  Serial.begin(9600);
  delay(1500);

  pinMode(Green_Led, OUTPUT);
  pinMode(Red_Led, OUTPUT);
  pinMode(pir_pin, INPUT);

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);  
  ArduinoCloud.printDebugInfo();
}
void loop() {
  ArduinoCloud.update();
  gas_Val = analogRead(Gas_pin) ;
  int pir = digitalRead(pir_pin);
  if(pir == 1) {
    digitalWrite(Green_Led, HIGH);
    pir_LED = true ;
    delay(3000);
    }
  else {
    digitalWrite(Green_Led, LOW);
    pir_LED = false ;
  }
  if(gas_Val > 150) {
    for(int i=1; i<6; i++){
      digitalWrite(Red_Led, HIGH);
      delay(300) ;
      digitalWrite(Red_Led, LOW);
      delay(300) ;
    }
    
  }
}
