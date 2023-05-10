#include <M5Core2.h>
#include <WiFi.h>
#include <time.h>

const char* ssid = "20200815me"; // WiFiのSSIDを入力してください
const char* password = "0815asdf"; // WiFiのパスワードを入力してください
const char* ntpServer = "pool.ntp.org"; // NTPサーバーのホスト名

const int timeZone = 9; // タイムゾーン（日本は+9）

void setup() {
  M5.begin();
  M5.Lcd.fillScreen(TFT_YELLOW);
  M5.Lcd.setTextSize(6);
  M5.Lcd.setTextColor(TFT_BLACK,TFT_YELLOW);

  // WiFiに接続
  Serial.println();
  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");
  
  // NTPサーバーから時刻情報を取得
  configTime(timeZone * 3600, 0, ntpServer);
  while (!time(nullptr)) {
    delay(100);
  }
}

void loop() {
  // 現在の時刻を取得
  time_t now = time(nullptr);
  struct tm timeinfo;
  localtime_r(&now, &timeinfo);

  // LCD画面に時刻を表示
  char formattedTime[16];
  sprintf(formattedTime, "%02d:%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print(formattedTime);

  delay(1000);
}
