#include "AWSPub.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "FS.h"
#include "SPIFFS.h"
#include "SPIFFSRead.h"
#include "payload.h"

// AWS IoT設定
//const char* aws_endpoint = "YOUR_AWS_IOT_ENDPOINT"; // AWS IoTエンドポイント
//const char* deviceName = "YOUR_DEVICE_NAME";
String gAwsEndpoint = "";
String gDeviceName = "";
const int aws_port = 8883;

String sanitizeEndpoint(String endpoint);


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
    //String awsDeviceName, awsEndpoint;
    while(configFile.available()) {
        String line = configFile.readStringUntil('\n');
        line.trim();
        int separatorIndex = line.indexOf(':');
        if (separatorIndex != -1) {
            String key = line.substring(0, separatorIndex);
            String value = line.substring(separatorIndex + 1);

            if (key == "AWS_DEVICE_NAME") {
                gDeviceName = value;
            } else if (key == "AWS_IOT_ENDPOINT") {
                gAwsEndpoint = value;
            }
        }
    }
    configFile.close();

    // 変数に読み込んだ値を設定
    //const char* aws_endpoint = awsEndpoint.c_str();
    //const char* deviceName = awsDeviceName.c_str();
    //awsEndpoint = sanitizeEndpoint(awsEndpoint);

    //aws_endpoint = awsEndpoint.c_str();
    //deviceName = awsDeviceName.c_str();
    Serial.println("AWS IoTエンドポイント: " + gAwsEndpoint);
    Serial.println("デバイス名: " + gDeviceName);
}


String gCaContent = "";
String gCertificateContent = "";
String gPrivateKeyContent = "";


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
  File ca = SPIFFS.open("/key/AmazonRootCA1.pem", "r");
  if (!ca) {
      Serial.println("CA証明書ファイルの読み込みに失敗しました。");
  } else {
      Serial.println("CA証明書ファイルを読み込みました。");
      //String caContent = "";
      while (ca.available()) {
          gCaContent += char(ca.read());
      }
      Serial.print("CA証明書の内容の長さ: ");
      Serial.println(gCaContent.length()); // 読み込んだCA証明書の内容の長さを表示

      net.setCACert(gCaContent.c_str());
      ca.close();
  }

   if(!SPIFFS.begin(true)){
    Serial.println("SPIFFSの初期化に失敗しました。");
    return;
  }


  // 拡張子に基づいて証明書とキーを読み込む
  gCertificateContent = SPIFFSRead::readFirstFileWithExtension(".cert.pem");
  gPrivateKeyContent = SPIFFSRead::readFirstFileWithExtension(".private.key");

  // 読み込んだ内容でセットアップ
  if(gCertificateContent.length() > 0 && gPrivateKeyContent.length() > 0) {
    net.setCertificate(gCertificateContent.c_str());
    net.setPrivateKey(gPrivateKeyContent.c_str());

    // 内容の長さを出力する
    Serial.print("証明書の長さ: ");
    Serial.println(gCertificateContent.length());
    Serial.print("プライベートキーの長さ: ");
    Serial.println(gPrivateKeyContent.length());
  } else {
    Serial.println("証明書またはプライベートキーが見つかりませんでした。");
  }

  //client.setClient(net);
  // AWS IoTエンドポイントの設定
  client.setServer(gAwsEndpoint.c_str(), aws_port);

  //client.setKeepAlive(60);


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
      while (!client.connect(gDeviceName.c_str())) {
        delay(1000);
      }
    }

    // 現在の時刻をミリ秒で取得
    unsigned long currentTime = millis();

    #if 1
    // ペイロードを動的に生成
    String payload = createJsonPayload(
      gDeviceName, 
      "デバイスID", 
      "所属組織", 
      currentTime, 
      "センサー情報", 
      "ボタン状態", 
      "定時監視データ", 
      "予備データ1", 
      "予備データ2"
      );

    Serial.print("Payload size: ");
    Serial.println(payload.length()); // ペイロードのサイズを出力
    // 生成されたペイロードをAWS IoTに送信
    if(client.publish("topic/path", payload.c_str())){
      Serial.println("AWS IoTにデータを送信しました。");
    } else {
      Serial.println("AWS IoTへのデータ送信に失敗しました。");
    }
    
    #endif

    #if 0
    // データをAWS IoTに送信
    String payload = "{\"temperature\": 25.5}";
    client.publish("topic/path", payload.c_str());
    Serial.println("AWS IoTにデータを送信しました。");
    #endif

    //delay(60000); // 1分ごとに送信
    delay(30000); // 30secごとに送信
  }
}

