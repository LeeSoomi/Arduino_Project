int speed=200;
int ENA1 = 5 ;
int IN1 =  6 ;
int IN2 = 7 ;
int ENA2 = 8 ;
int IN3 =  9;
int IN4 = 10 ;

void setup(){
 pinMode(ENA1, OUTPUT) ;
 pinMode(IN1, OUTPUT) ; 
 pinMode(IN2, OUTPUT) ; 
 pinMode(ENA2, OUTPUT) ;
 pinMode(IN3, OUTPUT) ; 
 pinMode(IN4, OUTPUT) ;  
}

void loop(){
  forward();
  delay(1000) ;
  stop();
  delay(1000) ; 
  backward() ;
  delay(1000) ;
  stop();
  delay(1000) ; 
  left();
  delay(1000) ;
  stop();
  delay(1000) ; 
  right() ;
  delay(1000) ;
  stop();
  delay(1000) ; 
  
}

void forward(){
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,LOW);
   analogWrite(ENA1,speed);
   digitalWrite(IN3,HIGH);
   digitalWrite(IN4,LOW);
   analogWrite(ENA2,speed); 
}
void backward(){
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,HIGH);
   analogWrite(ENA1,speed);
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,HIGH);
   analogWrite(ENA2,speed); 
}

void right(){
   digitalWrite(IN1,LOW);
   digitalWrite(IN2,HIGH);
   analogWrite(ENA1,speed);
   digitalWrite(IN3,HIGH);
   digitalWrite(IN4,LOW);
   analogWrite(ENA2,speed); 
}

void left(){
   digitalWrite(IN1,HIGH);
   digitalWrite(IN2,LOW);
   analogWrite(ENA1,speed);
   digitalWrite(IN3,LOW);
   digitalWrite(IN4,HIGH);
   analogWrite(ENA2,speed); 
}

void stop(){
   analogWrite(ENA1,0);
   analogWrite(ENA2,0);
}
