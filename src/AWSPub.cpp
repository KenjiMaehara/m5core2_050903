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

WiFiClientSecure net;
PubSubClient client(net);



// AWS IoT設定（エンドポイント、認証情報など）
// 以前の設定をここに移動

WiFiClientSecure net;
PubSubClient client(net);

void setupAWSIoT() {
  // WiFi接続とAWS IoTの設定
  // 以前のsetup関数から関連部分をここに移動
}

void sendDataToAWS(void * parameter) {
  // データ送信処理
  // 以前のsendDataToAWS関数の内容をここに移動
}