#include <M5Core2.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

// WiFi設定
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";



void setup() {
  M5.begin();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  net.setCACert(rootCA);
  net.setCertificate(certificate);
  net.setPrivateKey(privateKey);

  client.setServer(aws_endpoint, aws_port);

  // タスクの作成と開始
  xTaskCreatePinnedToCore(
    sendDataToAWS, /* タスク関数 */
    "SendAWSTask", /* タスク名 */
    10000,         /* スタックサイズ */
    NULL,          /* タスクパラメータ */
    1,             /* 優先度 */
    NULL,          /* タスクハンドル */
    0              /* コアID */
  );
}

void loop() {
  // ここでは何もしない
}

// AWSへデータを送信するタスク
void sendDataToAWS(void * parameter){
  for(;;){ // 無限ループ
    if (!client.connected()) {
      while (!client.connect(deviceName)) {
        delay(1000);
      }
    }

    // データをAWS IoTに送信
    String payload = "{\"temperature\": 25.5}";
    client.publish("topic/path", payload.c_str());

    delay(60000); // 1分ごとに送信
  }
}