#include <M5Core2.h>
#include <WiFi.h>

const char* ssid;
const char* password;

void connectToWiFi();


void setup() {
  M5.begin();
  //M5.Power.begin();
  M5.Lcd.clear();

  // SRAM領域からSSIDとパスワードを読み込む
  ssid = (const char*)RTC_SLOW_MEM;
  password = (const char*)RTC_SLOW_MEM + strlen(ssid) + 1;

  // SRAM領域に保存されたSSIDとパスワードが空でない場合、Wi-Fiに接続する
  if (strlen(ssid) > 0 && strlen(password) > 0) {
    connectToWiFi();
  } else {
    // Wi-Fi設定モードを開始
    WiFi.beginSmartConfig();

    // Wi-Fi接続待機
    while (!WiFi.smartConfigDone()) {
      delay(500);
      M5.Lcd.print(".");
    }

    // Wi-Fiに接続したらSSIDとパスワードを保存
    strcpy((char*)RTC_SLOW_MEM, WiFi.SSID().c_str());
    strcpy((char*)RTC_SLOW_MEM + strlen(ssid) + 1, WiFi.psk().c_str());
  }
}

void loop() {
  // メインの処理をここに記述

  // Wi-Fiが切断された場合、再接続を試みる
  if (WiFi.status() != WL_CONNECTED) {
    connectToWiFi();
  }
  
  // その他の処理をここに記述
}

void connectToWiFi() {
  M5.Lcd.clear();
  M5.Lcd.println("Connecting to Wi-Fi...");

  // 保存されたSSIDとパスワードを使用してWi-Fiに接続
  WiFi.begin(ssid, password);
  
  // Wi-Fi接続待機
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Lcd.print(".");
  }

  M5.Lcd.clear();
  M5.Lcd.println("Wi-Fi Connected");
}
