#include <M5Core2.h>
#include "CUF_24px.h"  // フォントファイルをインクルード

#include <HTTPClient.h>
#include <ArduinoJson.h>

extern void displayTime_every_second(); 
extern String gLocationInfo;  // main.cpp など他のファイルで宣言された gLocationInfo を参照

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


const char* apiKey = "Your_OpenWeatherMap_API_Key";  // APIキー
extern String gCity;

void displayLocationWeather(int duration) {

  M5.update();
  M5.Lcd.fillScreen(TFT_BLACK);

  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextFont(1);
  M5.Lcd.setTextSize(1);


  if (gLocationInfo != "Location: Unknown") {
    HTTPClient http;
    String weatherUrl = "http://api.openweathermap.org/data/2.5/weather?q=" + gLocationInfo + "&appid=" + String(apiKey) + "&units=metric";
    http.begin(weatherUrl);
    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, payload);
      String weather = doc["weather"][0]["main"].as<String>();
      float temp = doc["main"]["temp"].as<float>();

      M5.Lcd.fillScreen(TFT_BLACK);
      M5.Lcd.setCursor(0, 0);
      M5.Lcd.println("Location: " + gCity);
      M5.Lcd.println("Weather: " + weather);
      M5.Lcd.println("Temperature: " + String(temp) + " C");
    } else {
      M5.Lcd.println("Error getting weather data");
    }
    http.end();
  } else {
    M5.Lcd.fillScreen(TFT_BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println("Location information is not available.");
  }

  delay(duration);
}


void displayLocationWeather_02(int duration) {
  // 現在地の天気を表示するコード
  M5.update();
  M5.Lcd.fillScreen(TFT_BLACK);
  // 現在地情報を表示
  // 日本語の表示部分でフォントを使用
  M5.Lcd.setFreeFont(&unicode_24px);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setCursor(10, 200);
  M5.Lcd.drawString(gLocationInfo, 10, 200);

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
  M5.Lcd.drawString(gLocationInfo, 10, 200);

  delay(duration);
}

