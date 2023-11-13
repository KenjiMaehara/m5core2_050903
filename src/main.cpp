#include <M5Core2.h>
#include <WiFi.h>
#include <time.h>

// WiFi設定 - ここにあなたのWiFiのSSIDとパスワードを入力してください
const char* ssid = "20230616me_IPv6";
const char* password = "asdf0616";

// NTPサーバーの設定
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 3600 * 9;  // GMT+9:00 for Japan
const int   daylightOffset_sec = 0;

void setup() {
  // M5Stack Core2の初期化
  M5.begin();

  // WiFi接続
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Lcd.print(".");
  }
  
  // NTPサーバーから時刻を取得
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  // LCDの設定
  M5.Lcd.setTextSize(2);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.fillScreen(BLACK);
}

void loop() {
  // 現在の時刻を取得
  time_t now;
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    M5.Lcd.print("Failed to obtain time");
    return;
  }
  now = mktime(&timeinfo);

  // 日付と曜日をフォーマット
  char strftime_buf[64];
  strftime(strftime_buf, sizeof(strftime_buf), "%m/%d (%a)", &timeinfo);

  // LCDに日付を表示
  M5.Lcd.setCursor(10, 10);
  M5.Lcd.print(strftime_buf);

  // 1秒待機
  delay(1000);
}
