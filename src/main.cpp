#include <M5Core2.h>

void setup() {
  M5.begin();
  M5.Lcd.println("Press the left button");
  Serial.println("test start");
}

void loop() {
  M5.update();
  if (M5.BtnA.wasPressed()) {
    M5.Lcd.fillScreen(TFT_BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Lcd.setTextSize(2);
    M5.Lcd.println("hello world");
    Serial.println("pushed A");
  }
}