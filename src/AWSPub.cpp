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


void readAWSDeviceName() {
    if(!SPIFFS.begin(true)){
        Serial.println("SPIFFSの初期化に失敗しました。");
        return;
    }

    // AWS設定ファイルを開く
    File configFile = SPIFFS.open("/aws_devicename.conf", "r");
    if (!configFile) {
        Serial.println("AWS設定ファイルを開くことができませんでした。");
        return;
    }

    // ファイルからデバイス名とエンドポイントを読み込む
    String awsDeviceName, awsEndpoint;
    while(configFile.available()) {
        String line = configFile.readStringUntil('\n');
        line.trim();
        int separatorIndex = line.indexOf(':');
        if (separatorIndex != -1) {
            String key = line.substring(0, separatorIndex);
            String value = line.substring(separatorIndex + 1);

            if (key == "AWS_DEVICE_NAME") {
                awsDeviceName = value;
            } else if (key == "AWS_IOT_ENDPOINT") {
                awsEndpoint = value;
            }
        }
    }
    configFile.close();

    // 変数に読み込んだ値を設定
    const char* aws_endpoint = awsEndpoint.c_str();
    const char* deviceName = awsDeviceName.c_str();
    Serial.println("AWS IoTエンドポイント: " + awsEndpoint);
    Serial.println("デバイス名: " + awsDeviceName);
}


void setupAWSIoT() {

   if(!SPIFFS.begin(true)){
    Serial.println("SPIFFSの初期化に失敗しました。");
    return;
  }

  readAWSDeviceName();

   if(!SPIFFS.begin(true)){
    Serial.println("SPIFFSの初期化に失敗しました。");
    return;
  }


  // Amazon Root CA 1証明書を読み込む
  File ca = SPIFFS.open("/AmazonRootCA1.pem", "r");
  if (!ca) {
      Serial.println("CA証明書ファイルの読み込みに失敗しました。");
  } else {
      Serial.println("CA証明書ファイルを読み込みました。");
      String caContent = "";
      while (ca.available()) {
          caContent += char(ca.read());
      }
      net.setCACert(caContent.c_str());
      ca.close();
  }

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

    // 内容の長さを出力する
    Serial.print("証明書の長さ: ");
    Serial.println(certificateContent.length());
    Serial.print("プライベートキーの長さ: ");
    Serial.println(privateKeyContent.length());
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