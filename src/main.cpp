#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiMulti.h>
#include <SPI.h>

WiFiMulti wifiMulti;

void setup() {
  Serial.begin(115200);
  
  // スマートコンフィグを開始
  WiFi.beginSmartConfig();
  
  // WiFi接続の待機
  while (!WiFi.smartConfigDone()) {
    delay(500);
    Serial.print(".");
  }
  
  // WiFi接続が確立されたら設定を表示
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("SSID: " + WiFi.SSID());
  Serial.println("Password: " + WiFi.psk());
  
  // オートリコネクトを有効化
  WiFi.setAutoReconnect(true);
  
  // WiFiMultiに追加
  //wifiMulti.addAP(WiFi.SSID(), WiFi.psk());
  wifiMulti.addAP(WiFi.SSID().c_str(), WiFi.psk().c_str());

}

void loop() {
  // WiFi接続の状態をチェック
  if (wifiMulti.run() == WL_CONNECTED) {
    // 接続成功時の処理をここに記述する
    // 例えば、センサーデータの送信など
  }
}
