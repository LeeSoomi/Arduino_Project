int led = 13;       
int flamePin = 5;           
int Flame = 1 ; 

void setup() {
  pinMode(led, OUTPUT);    
  pinMode(flamePin, INPUT);   
  Serial.begin(9600);      
}
 
void loop() {
  Flame = digitalRead(flamePin);
  if (Flame== 0){
    Serial.println("Fire!!!");
    digitalWrite(led, HIGH);
  }
  else{
    Serial.println("No worries");
    digitalWrite(led, LOW);
  }
}
