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
    for(int i=1 ; i<5; i++){
    digitalWrite(Led , HIGH );
    delay(300); 
    digitalWrite(Led , LOW );
    delay(200);      
    }        
  }  else {                                  
    Serial.println("  ");                   
  }
  delay(100);                             
}
