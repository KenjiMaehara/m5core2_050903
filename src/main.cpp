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


  setupAWSIoT();

  //のwhile(1);

}





void loop() {
  // ここでは何もしない
}

