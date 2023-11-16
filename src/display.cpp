#include <M5Core2.h>
#include "CUF_24px.h"  // フォントファイルをインクルード

extern void displayTime_every_second(); 
extern String locationInfo;  // main.cpp など他のファイルで宣言された locationInfo を参照

void displayTime(int duration) {
  // 時刻を表示するコード
  M5.update();
  M5.Lcd.fillScreen(TFT_BLACK);

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

  delay(duration);

}

void displayWeather(int duration) {
  // 天気情報を取得して表示するコード
  M5.update();
  M5.Lcd.fillScreen(TFT_BLACK);

  // 日本語の表示部分でフォントを使用
  M5.Lcd.setFreeFont(&unicode_24px);
  M5.Lcd.setTextSize(2);
 
  // テキストの幅と高さを取得
  int textWidth = M5.Lcd.textWidth("今日のてんき");
  int textHeight = 24;  // 24pxフォントの高さ

  // テキストを中央に配置
  int x = (320 - textWidth) / 2;    // 画面の幅からテキストの幅を引いて2で割る
  int y = (240 - textHeight) / 2;   // 画面の高さからテキストの高さを引いて2で割る

  M5.Lcd.setCursor(x, y);
  M5.Lcd.drawString("今日のてんき", x, y);


  delay(duration);
}

void displayLocationWeather(int duration) {
  // 現在地の天気を表示するコード
  M5.update();
  M5.Lcd.fillScreen(TFT_BLACK);
  // 現在地情報を表示
  // 日本語の表示部分でフォントを使用
  M5.Lcd.setFreeFont(&unicode_24px);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(10, 200);
  M5.Lcd.drawString(locationInfo, 10, 200);

  delay(duration);
}

void displayTemperatureAndHumidity(int duration) {
  // 温度と湿度を表示するコード
  M5.update();
  M5.Lcd.fillScreen(TFT_BLACK);
  // 現在地情報を表示
  // 日本語の表示部分でフォントを使用
  M5.Lcd.setFreeFont(&unicode_24px);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(10, 200);
  M5.Lcd.drawString(locationInfo, 10, 200);

  delay(duration);
}