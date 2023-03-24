void setup() {
  Serial.begin(115200);
  for(int i=1;  i<11 ; i++){
    Serial.print("I= ");
    Serial.println(i);
  }
}

void loop() {
  
}
