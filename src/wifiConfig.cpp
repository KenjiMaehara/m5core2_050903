#include <FS.h>          // ESP8266/ESP32ファイルシステムライブラリ
#include <SPIFFS.h>      // ESP8266/ESP32 SPIFFSライブラリ
#include <WiFi.h>        // ESP8266/ESP32 WiFiライブラリ
#include "wifiConfig.h"  // このスケッチのヘッダファイル
#include <M5Core2.h>

void setup_connectToWiFi() {

  // M5Core2の初期化
  M5.begin();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);

  // WiFi接続の設定...
  Serial.print("Connecting to WiFi");
  M5.Lcd.print("Connecting to WiFi");

  File wifiConfig = SPIFFS.open("/wifi_SSID.conf", "r");
  if (!wifiConfig) {
    Serial.println("設定ファイルのオープンに失敗しました。");
    return;
  }

  while (wifiConfig.available()) {
    String line = wifiConfig.readStringUntil('\n');
    if (line.startsWith("#") || line.length() == 0) continue; // コメントまたは空行をスキップ

    int commaIndex = line.indexOf(',');
    if (commaIndex == -1) continue; // コンマが見つからない行をスキップ

    String ssid = line.substring(0, commaIndex);
    String password = line.substring(commaIndex + 1);

    ssid.trim();
    password.trim();

    Serial.print("接続を試みています: ");
    Serial.print(ssid);
    Serial.print(" パスワード長: ");
    Serial.println(password.length()); // パスワードの長さを出力

    WiFi.begin(ssid.c_str(), password.c_str());

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 30) {
      delay(500);
      Serial.print(".");
      M5.Lcd.print(".");  // LCD画面に"."を表示
      attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\nWiFiに接続しました。");
      Serial.print("IPアドレス: ");
      Serial.println(WiFi.localIP());

      M5.Lcd.println("Connected to WiFi.");
      M5.Lcd.print("IP Address: ");
      M5.Lcd.println(WiFi.localIP());
      
      delay(5000); // 5秒間待機

      M5.Lcd.fillScreen(BLACK); // 画面をクリアして表示を消す

      return;
    } else {
      Serial.println("\n接続に失敗しました。次のSSIDを試します。");
      M5.Lcd.println("Failed to connect to WiFi.");
    }
  }

  wifiConfig.close();
  Serial.println("全てのWiFiネットワークに接続できませんでした。");
}