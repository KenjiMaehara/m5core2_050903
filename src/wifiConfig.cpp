#include <FS.h>          // ESP8266/ESP32ファイルシステムライブラリ
#include <SPIFFS.h>      // ESP8266/ESP32 SPIFFSライブラリ
#include <WiFi.h>        // ESP8266/ESP32 WiFiライブラリ
#include "wifiConfig.h"  // このスケッチのヘッダファイル

void connectToWiFi() {
  if (!SPIFFS.begin()) {
    Serial.println("SPIFFSの初期化に失敗しました。");
    return;
  }

  File wifiConfig = SPIFFS.open("/wifi_SSID.conf", "r");
  if (!wifiConfig) {
    Serial.println("設定ファイルのオープンに失敗しました。");
    return;
  }

  while (wifiConfig.available()) {
    String ssid = wifiConfig.readStringUntil(',');
    String password = wifiConfig.readStringUntil('\n');
    ssid.trim(); // 余分な空白や改行を削除
    password.trim();

    WiFi.begin(ssid.c_str(), password.c_str());
    Serial.print("接続を試みています: ");
    Serial.println(ssid);

    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 30) { // 15秒間接続を試みる
      delay(500);
      Serial.print(".");
      attempts++;
    }

    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("\nWiFiに接続しました。");
      Serial.print("IPアドレス: ");
      Serial.println(WiFi.localIP());
      return; // 接続に成功したらループを抜ける
    } else {
      Serial.println("\n接続に失敗しました。次のSSIDを試します。");
    }
  }

  wifiConfig.close();
  Serial.println("全てのWiFiネットワークに接続できませんでした。");
}