#include <M5Core2.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

// WiFi設定
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

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
}

void loop() {
  if (!client.connected()) {
    while (!client.connect(deviceName)) {
      delay(1000);
    }
  }

  // ここでデータをAWS IoTに送信
  String payload = "{\"temperature\": 25.5}";
  client.publish("topic/path", payload.c_str());

  delay(60000); // 1分ごとに送信
}
