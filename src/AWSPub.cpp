#include "AWSPub.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "FS.h"
#include "SPIFFS.h"
#include "SPIFFSRead.h"

// AWS IoT設定
const char* aws_endpoint = "YOUR_AWS_IOT_ENDPOINT"; // AWS IoTエンドポイント
const char* deviceName = "YOUR_DEVICE_NAME";
const int aws_port = 8883;



// AWS IoT設定（エンドポイント、認証情報など）
// 以前の設定をここに移動

WiFiClientSecure net;
PubSubClient client(net);

void setupAWSIoT() {

   if(!SPIFFS.begin(true)){
    Serial.println("SPIFFSの初期化に失敗しました。");
    return;
  }

  // 拡張子に基づいて証明書とキーを読み込む
  String certificateContent = SPIFFSRead::readFirstFileWithExtension(".cert.pem");
  String privateKeyContent = SPIFFSRead::readFirstFileWithExtension(".private.key");

  // 読み込んだ内容でセットアップ
  if(certificateContent.length() > 0 && privateKeyContent.length() > 0) {
    net.setCertificate(certificateContent.c_str());
    net.setPrivateKey(privateKeyContent.c_str());
  } else {
    Serial.println("証明書またはプライベートキーが見つかりませんでした。");
  }


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