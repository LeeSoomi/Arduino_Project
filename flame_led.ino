int led = 13;       
int flame = 5;      
int state = 0;      
 
void setup() {
  pinMode(led, OUTPUT);    
  pinMode(flame, INPUT);   
  Serial.begin(9600);      
}
 
void loop() {
  state = digitalRead(flame);  
  digitalWrite(led, LOW);      
 
  if (state == 1){              
    Serial.println("ON");       
    digitalWrite(led, HIGH);    
    delay(100);                
  }
  else {                           
    Serial.println("OFF");     
    digitalWrite(led, LOW);     
  }
  delay(100);
}
