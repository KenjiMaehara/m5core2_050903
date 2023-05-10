#include <M5Core2.h>


void setup() {
  M5.begin();
  
  // ボタンA、ボタンB、ボタンCのイベントリスナーを設定
  //M5.BtnA.setPressedHandler(button_a_was_pressed);
  //M5.BtnB.setPressedHandler(button_b_was_pressed);
  //M5.BtnC.setPressedHandler(button_c_was_pressed);
}

void loop() {
  M5.update();

  if (M5.BtnA.wasPressed()) {
    M5.Lcd.clear();
    M5.Lcd.fillScreen(TFT_WHITE);
    M5.Lcd.setTextColor(TFT_GREEN);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.print("hello world");
  }

  if (M5.BtnB.wasPressed()) {
    M5.Lcd.clear();
    M5.Lcd.fillScreen(TFT_BLACK);
    M5.Lcd.setTextColor(TFT_YELLOW);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.print("hello world");
  }

  if (M5.BtnC.wasPressed()) {
    M5.Lcd.clear();
    M5.Lcd.fillScreen(TFT_YELLOW);
    M5.Lcd.setTextColor(TFT_RED);
    M5.Lcd.setTextSize(3);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.print("hello world");
  }

}