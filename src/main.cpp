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

  setupAWSIoT();


  while(1);
}





void loop() {
  // ここでは何もしない
}

