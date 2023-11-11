#include <M5Core2.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// WiFi設定
const char* ssid = "googlemain";
const char* password = "Fdsa@0813";

// NTPサーバー
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600 * 9;  // 日本のGMTオフセット（UTC+9）
const int   daylightOffset_sec = 0;    // 夏時間は日本では適用されない

// 現在地情報を格納するグローバル変数
String locationInfo = "Location: Unknown";

void displayTime();
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
}

void loop() {
  M5.update();
  displayTime();
  delay(1000);  // 1秒ごとに更新
}

void displayTime() {
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

  M5.Lcd.setTextSize(6);

  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setCursor(x, y);
  M5.Lcd.println(timeString);

  // 現在地情報を表示
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(10, 200);
  M5.Lcd.println(locationInfo);
}

void displayLocation() {
  HTTPClient http;
  http.begin("http://ip-api.com/json/");
  int httpCode = http.GET();

  if (httpCode > 0) {
    String payload = http.getString();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
    String city = doc["city"].as<String>();
    //String country = doc["country"].as<String>();

    locationInfo = city;
  } else {
    locationInfo = "Location: Unable to retrieve";
  }

  http.end();
}
