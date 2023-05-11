#include <M5Core2.h>
#include <WiFi.h>

void setup() {
  M5.begin();
  //M5.Power.begin();
  M5.Lcd.printf("Wi-Fi Configuration\n");
  delay(1000);
  
  // Wi-Fi設定モードを開始
  WiFi.beginSmartConfig();
  
  // Wi-Fi接続待機
  while (!WiFi.smartConfigDone()) {
    delay(500);
    M5.Lcd.print(".");
  }
  
  // Wi-Fi接続が完了したら、SSIDとパスワードを表示
  M5.Lcd.printf("\n\nWi-Fi Configuration Completed!\n");
  M5.Lcd.printf("SSID: %s\n", WiFi.SSID().c_str());
  M5.Lcd.printf("Password: %s\n", WiFi.psk().c_str());
  
  // 接続されたWi-Fiネットワークの詳細を表示
  M5.Lcd.printf("IP Address: %s\n", WiFi.localIP().toString().c_str());
  M5.Lcd.printf("Gateway: %s\n", WiFi.gatewayIP().toString().c_str());
  M5.Lcd.printf("Subnet Mask: %s\n", WiFi.subnetMask().toString().c_str());
}

void loop() {
  // 何もしない
}