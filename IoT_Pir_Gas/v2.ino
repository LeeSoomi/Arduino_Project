// delay 대신 mills 사용

#include "thingProperties.h"

const int pir_pin   = 4;   // D2 (PIR)
const int Green_Led = 13;  // D7 (Green)
const int Red_Led   = 2;   // D4 (Red)
const int Gas_pin   = A0;

// --- 동작 파라미터 ---
const unsigned long PIR_ON_MS       = 3000;  // PIR 감지 후 유지시간
const unsigned long BLINK_INTERVAL  = 300;   // 레드 LED 깜빡임 간격(ms)
const int           BLINK_TIMES     = 5;     // "켜짐" 기준 5회 (ON/OFF 10토글)
const int           GAS_THRESHOLD   = 150;

// --- PIR 상태 ---
bool pirActive = false;
unsigned long pirDeadline = 0;  // 이 시각까지 그린 LED 유지

// --- 가스 LED(점멸) 상태 ---
bool redBlinking = false;
unsigned long nextRedToggleAt = 0;
int togglesLeft = 0;             // 남은 토글 횟수 (ON/OFF 합산)
bool redState = false;           // 현재 레드 LED 상태

void setup() {
  Serial.begin(9600);
  delay(1500);

  pinMode(Green_Led, OUTPUT);
  pinMode(Red_Led, OUTPUT);
  pinMode(pir_pin, INPUT);

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  digitalWrite(Green_Led, LOW);
  digitalWrite(Red_Led, LOW);
}

void loop() {
  ArduinoCloud.update();

  unsigned long now = millis();

  // --- 센서 읽기 ---
  gas_Val = analogRead(Gas_pin);
  int pir = digitalRead(pir_pin);

  // --- PIR 처리: 감지되면 3초 유지 마감시각 갱신 ---
  if (pir == HIGH) {
    pirActive = true;
    pirDeadline = now + PIR_ON_MS;   // 또는: pirDeadline = now; 유지 로직에서 (now - pirStart) 비교 방식도 OK
  }

  // --- PIR LED 구동(논블로킹) ---
  if (pirActive && ( (long)(pirDeadline - now) > 0 )) {
    digitalWrite(Green_Led, HIGH);
    pir_LED = true;
  } else {
    digitalWrite(Green_Led, LOW);
    pir_LED = false;
    pirActive = false;
  }

  // --- 가스 임계 도달 시, 점멸 시퀀스 "시작"만 트리거 ---
  if (gas_Val > GAS_THRESHOLD && !redBlinking) {
    redBlinking = true;
    togglesLeft = BLINK_TIMES * 2;  // ON/OFF 합산 토글 수
    nextRedToggleAt = now;          // 즉시 첫 토글
    redState = false;               // 시작은 꺼짐 기준 → 첫 토글에서 켜짐
  }

  // --- 점멸 시퀀스 수행(논블로킹) ---
  if (redBlinking && (long)(now - nextRedToggleAt) >= 0) {
    redState = !redState;
    digitalWrite(Red_Led, redState);
    nextRedToggleAt += BLINK_INTERVAL;
    togglesLeft--;

    if (togglesLeft <= 0) {
      redBlinking = false;
      redState = false;
      digitalWrite(Red_Led, LOW);
    }
  }

  // (필요 시) 여기에서 추가 로직/다른 센서도 동시에 처리 가능
}
