
int led = 4 ;
void setup() {
  Serial.begin(115200); 
  pinMode(led,OUTPUT);
}
 
void loop() {
  while(Serial.available()) {
    char incom = Serial.read();
    if( incom == '1'){
      digitalWrite(led, HIGH);
    }
    else if( incom == '0'){
      digitalWrite(led, LOW);
    }
  }
}
