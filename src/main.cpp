#include <M5Core2.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include "AWSPub.h"
#include "FS.h"
#include "SPIFFS.h"
#include "wifiConfig.h"
#include "SPIFFSRead.h"

// WiFi設定
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";



void setup() {

  SPIFFS_check();


  connectToWiFi();

  IPAddress dns(8,8,8,8); // GoogleのDNS
  WiFi.config(IPAddress(0,0,0,0), IPAddress(0,0,0,0), IPAddress(0,0,0,0), dns);
  Serial.println("DNS 8.8.8.8 手動指定完了");

  delay(1000);

  // DNS解決テスト
  Serial.print("www.yahoo.comのIPアドレスを解決しています...");
  IPAddress remote_ip;
  if(WiFi.hostByName("www.yahoo.com", remote_ip)) {
    Serial.print("成功: ");
    Serial.println(remote_ip);
  } else {
    Serial.println("失敗: 名前解決に失敗しました。");
  }

  //while(1);


  setupAWSIoT();

  //のwhile(1);

}





void loop() {
  // ここでは何もしない
}

