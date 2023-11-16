
#include <M5Core2.h>
#include "CUF_24px.h"  // フォントファイルをインクルード

extern String locationInfo;  // main.cpp など他のファイルで宣言された locationInfo を参照

void displayTime_every_second() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    M5.Lcd.println("Failed to obtain time");
    return;
  }

  char timeString[10];
  sprintf(timeString, "%02d:%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);

  int textWidth = M5.Lcd.textWidth(timeString);
  int textHeight = 30;

  int x = 0;
  int y = (240 - textHeight) / 2 - 20;
  
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextFont(1);
  M5.Lcd.setTextSize(6);

  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setCursor(x, y);
  M5.Lcd.println(timeString);

  // 現在地情報を表示
  // 日本語の表示部分でフォントを使用
  M5.Lcd.setFreeFont(&unicode_24px);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(10, 200);
  M5.Lcd.drawString(locationInfo, 10, 200);
}