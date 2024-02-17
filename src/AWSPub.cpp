#include "AWSPub.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// AWS IoT設定
const char* aws_endpoint = "YOUR_AWS_IOT_ENDPOINT"; // AWS IoTエンドポイント
const char* deviceName = "YOUR_DEVICE_NAME";
const int aws_port = 8883;

// 証明書
const char* rootCA = R"EOF(
-----BEGIN CERTIFICATE-----
YOUR_ROOT_CA_CERTIFICATE
-----END CERTIFICATE-----
)EOF";

const char* certificate = R"KEY(
-----BEGIN CERTIFICATE-----
YOUR_DEVICE_CERTIFICATE
-----END CERTIFICATE-----
)KEY";

const char* privateKey = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
YOUR_DEVICE_PRIVATE_KEY
-----END RSA PRIVATE KEY-----
)KEY";


// AWS IoT設定（エンドポイント、認証情報など）
// 以前の設定をここに移動

WiFiClientSecure net;
PubSubClient client(net);

void setupAWSIoT() {
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