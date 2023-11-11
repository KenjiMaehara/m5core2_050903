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

void displayTime();
void displayLocation();

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
}

void loop() {
  M5.update();
  displayTime();
  displayLocation();
  delay(10000);  // 10秒ごとに更新
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

  int x = (320 - textWidth) / 2;
  int y = (240 - textHeight) / 2 - 20;

  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setCursor(x, y);
  M5.Lcd.println(timeString);
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
    String country = doc["country"].as<String>();

    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(10, 200);
    M5.Lcd.println("Location: " + city + ", " + country);
  } else {
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(10, 200);
    M5.Lcd.println("Location: Unable to retrieve");
  }

  http.end();
}
