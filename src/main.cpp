#include <M5Core2.h>

#define BUZZER_PIN 25 // ブザーに接続されたピン番号

void setup() {
  M5.begin();
  Serial.println("test start");
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  M5.update();
  if (M5.BtnA.wasReleased()) {
    // ビープ音を鳴らす
    //M5.Speaker.tone(1000, 500); // 周波数1000Hz、長さ500msのビープ音
    tone(BUZZER_PIN, 1000, 500); // ピン番号、周波数1000Hz、長さ500msのビープ音
    delay(500); // 500ms待機して音を停止
    noTone(BUZZER_PIN); // ブザーを停止


    //M5.Lcd.println("beepsound");
    Serial.println("beepsound");
  }
}