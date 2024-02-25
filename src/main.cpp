#include <M5Core2.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include "AWSPub.h"
#include "FS.h"
#include "SPIFFS.h"
#include "wifiConfig.h"
#include "SPIFFSRead.h"
#include "button.h"

// WiFi設定
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";



void setup() {

  SPIFFS_check();

  IPAddress dns(8,8,8,8); // GoogleのDNS
  WiFi.config(IPAddress(0,0,0,0), IPAddress(0,0,0,0), IPAddress(0,0,0,0), dns);
  
  connectToWiFi();


  delay(1000);


  setupAWSIoT();

  buttonsetup();

  //のwhile(1);

}





void loop() {
  // ここでは何もしない
  delay(100);
}

