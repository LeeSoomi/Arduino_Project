int PIR = 5 ;  
int Led = 13 ;

void setup() {
  Serial.begin(9600);        
  pinMode(PIR, INPUT); 
  pinMode(Led, OUTPUT); 
  digitalWrite(Led ,LOW);    
}
void loop( ) {
  if (digitalRead(PIR) == HIGH) {        
    Serial.println("SENSOR ON");     
    digitalWrite(Led , HIGH );
    delay(200);         
  }  
  else {                                  
    Serial.println("SENSOR OFF"); 
    digitalWrite(Led , LOW );                  
  }
  delay(100);                             
}
