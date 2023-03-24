void setup() {
  Serial.begin(115200);
  Serial.println("구구단 출력하기 ");
  delay(1000);
  for(int nf=2;  nf<10 ; nf++){
    Serial.print(nf);
    Serial.println(" 단입니다.");
    for(int ns=1; ns<10; ns++){
      Serial.print(nf);
      Serial.print(" * ");
      Serial.print(ns);
      Serial.print(" = ");
      Serial.println(nf*ns);
      delay(500);
    }
    delay(1000);
    Serial.println( );
  }
}

void loop() {
  
}
