#include <M5Core2.h>
#include "CUF_24px.h"  // フォントファイルをインクルード

#include <HTTPClient.h>
#include <ArduinoJson.h>

extern void displayTime_every_second(); 
extern String gLocationInfo;  // main.cpp など他のファイルで宣言された gLocationInfo を参照

int x_position = 0;
int y_position = 0;
int icon_width = 64;
int icon_height = 64;

void displayTime(int duration) {
  // 時刻を表示するコード
  M5.update();
  M5.Lcd.fillScreen(TFT_BLACK);

  M5.Lcd.setTextFont(1);
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.setTextSize(10);

  M5.Lcd.drawJpgFile(SD, "/picture03.jpg", x_position, y_position);

  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    M5.Lcd.println("Failed to obtain time");
    return;
  }

  char timeString[10];
  //sprintf(timeString, "%02d:%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
  sprintf(timeString, "%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min);

  int textWidth = M5.Lcd.textWidth(timeString);
  int textHeight = 30;

  // テキストを中央に配置
  int x = (320 - textWidth) / 2;    // 画面の幅からテキストの幅を引いて2で割る
  int y = (240 - textHeight) / 2 - 20;
  
  //M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setCursor(x, y);
  M5.Lcd.println(timeString);

  delay(duration);

}

void displayWeather(int duration) {
  // 天気情報を取得して表示するコード
  M5.update();
  M5.Lcd.fillScreen(TFT_BLACK);

  M5.Lcd.drawJpgFile(SD, "/picture01.jpg", x_position, y_position);

  // 日本語の表示部分でフォントを使用
  M5.Lcd.setFreeFont(&unicode_24px);
  M5.Lcd.setTextSize(2);
 
  // テキストの幅と高さを取得
  int textWidth = M5.Lcd.textWidth("今日のてんき");
  int textHeight = 24;  // 24pxフォントの高さ

  // テキストを中央に配置
  int x = (320 - textWidth) / 2;    // 画面の幅からテキストの幅を引いて2で割る
  int y = (240 - textHeight) / 2 - 20;   // 画面の高さからテキストの高さを引いて2で割る

  M5.Lcd.setCursor(x, y);
  M5.Lcd.drawString("今日のてんき", x, y);


  delay(duration);
}


void displayArea(int duration) {
  // 天気情報を取得して表示するコード
  M5.update();
  M5.Lcd.fillScreen(TFT_BLACK);

  M5.Lcd.drawJpgFile(SD, "/picture02.jpg", x_position, y_position);

  // 日本語の表示部分でフォントを使用
  M5.Lcd.setFreeFont(&unicode_24px);
  M5.Lcd.setTextSize(3);
 
  // テキストの幅と高さを取得
  int textWidth = M5.Lcd.textWidth(gLocationInfo);
  int textHeight = 24;  // 24pxフォントの高さ

  // テキストを中央に配置
  int x = (320 - textWidth) / 2;    // 画面の幅からテキストの幅を引いて2で割る
  int y = (240 - textHeight) / 2 - 20;   // 画面の高さからテキストの高さを引いて2で割る

  // テキストの色を赤に設定
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.setCursor(x, y);
  M5.Lcd.drawString(gLocationInfo, x, y);


  delay(duration);
}





//const char* apiKey = "Your_OpenWeatherMap_API_Key";  // APIキー
const char* apiKey = "4f97d65fe992fea7e3a6ab1f6fdb0ab8";  // APIキー
extern String gCity;

String gWeather;
float gTemp;
float precipitationProbability;


void displayLocationWeather(int duration) {

  M5.update();
  //M5.Lcd.fillScreen(TFT_BLACK);

  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextFont(1);
  M5.Lcd.setTextSize(3);


  if (gLocationInfo != "Location: Unknown") {
    HTTPClient http;

    String weatherUrl = "http://api.openweathermap.org/data/2.5/weather?q=" + gCity + "&appid=" + String(apiKey) + "&units=metric";
    http.begin(weatherUrl);
    int httpCode = http.GET();

    if (httpCode > 0) {
      String payload = http.getString();
      DynamicJsonDocument doc(1024);
      deserializeJson(doc, payload);
      gWeather = doc["weather"][0]["main"].as<String>();
      gTemp = doc["main"]["temp"].as<float>();
      precipitationProbability = doc["list"][0]["pop"].as<float>() * 100; // 降水確率 (%)

      M5.Lcd.fillScreen(TFT_BLACK);

      #if 1
      M5.Lcd.setCursor(0, 0);
      M5.Lcd.println("Location: " + gCity);
      M5.Lcd.println("Weather: " + gWeather);
      M5.Lcd.println("Temperature: " + String(gTemp) + " C");
      #endif



      if (gWeather == "Clear") {
        M5.Lcd.drawJpgFile(SD, "/sunny_icon.jpg", x_position, y_position);
      } else if (gWeather == "Clouds") {
        M5.Lcd.drawJpgFile(SD, "/cloudy_icon.jpg", x_position, y_position);
      } else if (gWeather == "Rain") {
        M5.Lcd.drawJpgFile(SD, "/rainy_icon.jpg", x_position, y_position);
      }



    } else {
      M5.Lcd.println("Error getting weather data");
    }
    http.end();
  } else {
    M5.Lcd.fillScreen(TFT_BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println("Location information is not available.");
  }

  // 現在地情報を表示
  // 日本語の表示部分でフォントを使用
  M5.Lcd.setFreeFont(&unicode_24px);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.setCursor(10, 200+20);
  //M5.Lcd.drawString(gLocationInfo, 10, 200);

  // 降水確率の表示
  M5.Lcd.println("降水確率: " + String(precipitationProbability) + "%");

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

