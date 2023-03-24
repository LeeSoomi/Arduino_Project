#include <WiFi.h>
#include "time.h"

const char* ssid       = "ROBOT_ROOM";
const char* password   = "16440110";

const char* ntpServer =  "pool.ntp.org";
const long  gmtOffset_sec = 32400; //GMT 기준으로 얼마나 차이나는지를 확인합니다.
                          // 한국은 그리니치 천문대 기준 9시간 추가된 시간대인, 
                          //"GMT+9" 이므로 "3600 * 9 = 32400" 만큼 더해주면 됩니다.
const int   daylightOffset_sec = 0 ; //서머타임 적용 지역이면, 
                            //한시간인 3600 을 적용하면 됩니다.
                          // 우리나라는 "0" 으로 정의합니다.

void printLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

void setup(){
  Serial.begin(115200);
  
  //connect to WiFi
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println(" CONNECTED");
  
  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop(){
  delay(1000);
  printLocalTime();
}
