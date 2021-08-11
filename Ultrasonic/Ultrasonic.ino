#define trigPin 13                 
#define echoPin 12  
           
void setup( ) {
  Serial.begin (9600);             
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);   
}

void loop( ) {
    digitalWrite(trigPin, LOW);
    digitalWrite(echoPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

  
  // echoPin 이 HIGH를 유지한 시간을 저장 한다.
    unsigned long duration = pulseIn(echoPin, HIGH); 
  // HIGH 였을 때 시간(초음파가 보냈다가 다시 들어온 시간)을 가지고 거리를 계산 한다.
  float distance = ((float)(340 * duration) / 10000) / 2;  
  
  Serial.print(distance);
  Serial.println("cm");
  // 수정한 값을 출력
  delay(500);                                       
}
