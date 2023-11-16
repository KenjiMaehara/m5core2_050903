#include <M5Core2.h>
#include <WiFi.h>
#include "CUF_24px.h"  // フォントファイルをインクルード

// WiFi設定
const char* ssid = "20230616me_IPv6";
const char* password = "asdf0616";

// NTPサーバー
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600 * 9;  // 日本のGMTオフセット（UTC+9）
const int   daylightOffset_sec = 0;    // 夏時間は日本では適用されない

// 現在地情報を格納するグローバル変数
String locationInfo = "Location: Unknown";


void displayLocation();  // 位置情報を取得する関数

void setup() {
  M5.begin();
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Lcd.println("Connecting to WiFi...");
  }

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.setTextSize(6);  // フォントサイズを大きくする

  displayLocation();  // 電源投入時に一度だけ位置情報を取得

  //M5.Lcd.setFreeFont(&unicode_24px);  // 日本語表示用のフォントを設定
}


extern void displayTime(int duration);
extern void displayWeather(int duration);
extern void displayLocationWeather(int duration);
extern void displayTemperatureAndHumidity(int duration);

void loop() {
  // 時刻を表示（10秒）
  displayTime(10000);

  // 天気情報を取得して表示（5秒）
  displayWeather(5000);

  // 現在地天気を表示（10秒）
  displayLocationWeather(10000);

  // 現在地の温度と湿度を表示（10秒）
  displayTemperatureAndHumidity(10000);
}
