#include "HUSKYLENS.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6
#define NUMPIXELS 3

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

long interval_red = 10000;
long interval_green = 15000;
long previousMillis = 0;

HUSKYLENS huskylens;
void printResult(HUSKYLENSResult result);

void setup() {
  Serial.begin(115200);
  Wire.begin();
    while (!huskylens.begin(Wire))
    {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(100);
    }

  pixels.begin();
  pixels.clear();
  pixels.show();
  delay(1000);
}

void loop() {
  pixels.clear();
  signalLamp();
  if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
  else
    {
      while (huskylens.available())
      {
        HUSKYLENSResult result = huskylens.read();
        if (result.command == COMMAND_RETURN_BLOCK){
          if (result.ID == 1){
            Serial.println("Detect Person!");
            pixels.setPixelColor(0, pixels.Color(150, 150, 0));
            pixels.show();
          }
          else{
            Serial.println("No Person!");
            pixels.setPixelColor(0, pixels.Color(0, 0, 0));
            pixels.show();
          }
        }
      }    
    }
}

void signalLamp(){
  unsigned long currentMillis = millis();
  Serial.println(currentMillis);

  if( currentMillis - previousMillis <= interval_red ) {
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.setPixelColor(1, pixels.Color(0, 0, 0));
    pixels.setPixelColor(2, pixels.Color(150, 0, 0));
    pixels.show();
  }
  else if( currentMillis - previousMillis > interval_red && currentMillis - previousMillis <= interval_green ) {
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.setPixelColor(1, pixels.Color(0, 150, 0));
    pixels.setPixelColor(2, pixels.Color(0, 0, 0));
    pixels.show();
  }
  else if (currentMillis - previousMillis > interval_green){
    previousMillis = currentMillis;
  }
}
