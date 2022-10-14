// 사용되는 라이브러리
#include <ThreeWire.h>  
#include <RtcDS1302.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm=Adafruit_PWMServoDriver();

ThreeWire myWire(4,5,2); // IO, SCLK, CE > RTC모듈 핀설정
RtcDS1302<ThreeWire> Rtc(myWire);

//초음파 핀 설정
#define trigPin 10                 
#define echoPin 9 

void setup () 
{
    pwm.begin();
    pwm.setPWMFreq(51); 
    pwm.setPWM(0,0,90); // 약
    pwm.setPWM(1,0,90); // 사료
    pwm.setPWM(2,0,90); // 문  

    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT);   
       
    Serial.begin(57600);
    Serial.print("compiled: ");
    Serial.print(__DATE__);
    Serial.println(__TIME__);
    delay(1000);
    
    Rtc.Begin();
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    Serial.println();
}

void loop () 
{   

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
    Serial.print("cm  ");
    
    // 초음파값이 10cm 이내일때 10초동안 문열고 닫기
    if(distance <= 10){
      pwm.setPWM(2,0,0);
      delay(10000);
      pwm.setPWM(2,0,90);
      delay(5000);
    }

    //실시간 시간 값을 RtcDateTime now에 저장 > 각각 변수로 분리 저장
    RtcDateTime now = Rtc.GetDateTime();
    int Hour = now.Hour();
    int Min = now.Minute();
    int Sec = now.Second();   
     
    Serial.print(Hour);
    Serial.print(" : ");    
    Serial.print(Min); 
    Serial.print(" : ");     
    Serial.println(Sec);    

    // 하루에 1번 약공급.. 오전 8시 > servo 0번
    if ((Hour== 8 && Min== 00 && Sec== 00)){
      pwm.setPWM(0,0,0);
      delay(1000);
      pwm.setPWM(0,0,90);
      delay(1000);
    }

    // 하루에 2번 사료공급.. 오전 10시, 오후 5시30 > servo 1번
    if ((Hour== 16 && Min== 00 && Sec== 00)||(Hour== 17 && Min== 30 && Sec== 00)){
      pwm.setPWM(1,0,0);
      delay(1000);
      pwm.setPWM(1,0,90);
      delay(1000);
    }    
    
    delay(1000); // one seconds
}
