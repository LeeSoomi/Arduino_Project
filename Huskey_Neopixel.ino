#include "HUSKYLENS.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6
#define NUMPIXELS 3

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

unsigned long interval_red = 10000;
unsigned long interval_green = 15000;
unsigned long previousMillis = 0;

unsigned long yellowHoldTime = 3000;      // 노란불 최소 유지 시간(ms)
unsigned long yellowStartMillis = 0;      // 노란불 시작 시간
bool yellowHolding = false;              // 노란불 유지 중인지

HUSKYLENS huskylens;

void setup() {
  Serial.begin(115200);
  Wire.begin();

  while (!huskylens.begin(Wire)) {
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

bool detectPersonID1() {
  bool detected = false;

  if (!huskylens.request()) {
    Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
    return false;
  }

  while (huskylens.available()) {
    HUSKYLENSResult result = huskylens.read();

    if (result.command == COMMAND_RETURN_BLOCK) {
      if (result.ID == 1) detected = true;
    }
  }

  return detected;
}

void showYellowOnly() {
  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(150, 150, 0)); // 노란색
  pixels.setPixelColor(1, pixels.Color(0, 0, 0));     // 초록 끔
  pixels.setPixelColor(2, pixels.Color(0, 0, 0));     // 빨강 끔
  pixels.show();
}

void showSignalLamp() {
  unsigned long currentMillis = millis();
  unsigned long elapsed = currentMillis - previousMillis;

  if (elapsed <= interval_red) {
    pixels.clear();
    pixels.setPixelColor(2, pixels.Color(150, 0, 0)); // 빨강
    pixels.show();
  }
  else if (elapsed <= (interval_red + interval_green)) {
    pixels.clear();
    pixels.setPixelColor(1, pixels.Color(0, 150, 0)); // 초록
    pixels.show();
  }
  else {
    previousMillis = currentMillis;
  }
}

void loop() {
  unsigned long now = millis();
  bool personDetected = detectPersonID1();

  // 사람이 감지되면 노란불 상태 시작 또는 유지
  if (personDetected) {
    if (!yellowHolding) {
      yellowHolding = true;
      yellowStartMillis = now;   // 노란불 시작 시간 기록
    }
    showYellowOnly();
    Serial.println("Detect Person!");
    return;
  }

  // 사람이 더 이상 감지되지 않더라도,
  // 노란불은 yellowHoldTime 동안은 계속 유지
  if (yellowHolding) {
    if (now - yellowStartMillis < yellowHoldTime) {
      showYellowOnly();
      Serial.println("Yellow holding...");
      return;
    } else {
      yellowHolding = false;  // 유지시간 끝나면 해제
    }
  }

  // 노란불 유지조건이 끝나면 일반 신호등 모드
  Serial.println("No Person!");
  showSignalLamp();
}
