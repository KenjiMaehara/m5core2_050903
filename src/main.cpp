#include <M5Core2.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>
#include "AWSPub.h"
#include "FS.h"
#include "SPIFFS.h"

// WiFi設定
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";


void SPIFFS_check();


void setup() {

  SPIFFS_check();

  M5.begin();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  setupAWSIoT();

  
}


void SPIFFS_check() {
  M5.begin();
  Serial.begin(115200);
  if (!SPIFFS.begin(true)) {
    Serial.println("SPIFFSのマウントに失敗しました");
    return;
  }

  Serial.println("SPIFFS内のファイル:");
  File root = SPIFFS.open("/");
  File file = root.openNextFile();
  while(file){
    Serial.print("ファイル名: ");
    Serial.println(file.name());
    // ファイルの内容を読み出して表示
    while(file.available()){
      Serial.write(file.read());
    }
    file = root.openNextFile();
  }
}



void loop() {
  // ここでは何もしない
}

