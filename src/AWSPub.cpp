#include "AWSPub.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "FS.h"
#include "SPIFFS.h"
#include "SPIFFSRead.h"

char rootCA[2000];
char certificate[2000];
char privateKey[2000];

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

    #if 1

    std::string temp = "\"" + std::string(awsEndpoint.c_str()) + "\"";
    aws_endpoint = temp.c_str();
    std::string temp02 = "\"" + std::string(awsDeviceName.c_str()) + "\"";
    deviceName = temp02.c_str();
  

    //aws_endpoint = awsEndpoint.c_str();
    //deviceName = awsDeviceName.c_str();
    Serial.println("AWS IoTエンドポイント: " + awsEndpoint);
    Serial.println("デバイス名: " + awsDeviceName);
    #endif
}

void readFile(fs::FS &fs, const char * dirname, String path , int num);

void setupAWSIoT() {

  readAWSDeviceName();

  //  Serial.println("write ca");
  readFile(SPIFFS, "/", "AmazonRootCA1.cer", 0); //含まれているものを探して、書き込む
  readFile(SPIFFS, "/", "certificate.pem.crt", 1);
  readFile(SPIFFS, "/", "private.pem.key", 2);

  const char* root = rootCA;
  const char* cer = certificate;
  const char* priv = privateKey;

  // Configure WiFiClientSecure to use the AWS IoT device credentials
  net.setCACert(root);
  net.setCertificate(cer);
  net.setPrivateKey(priv);

  //client.setClient(net);
  // AWS IoTエンドポイントの設定
  client.setServer(aws_endpoint, 8883);


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
    Serial.println("AWS IoTにデータを送信しました");

    delay(60000); // 1分ごとに送信
  }
}



void readFile(fs::FS &fs, const char * dirname, String path , int num) {

  String targetString;
  char* result = "no data";
  File root = fs.open(dirname);//どのディレクションを開くか
  File file = root.openNextFile();
  while (file) {//ここでファイル名を検索、違っていれば次のを拾いにいく。
    String res = file.name();
    if (res.indexOf(path) != -1) {
      targetString = res;
      break;
    }
    file = root.openNextFile();
  }

  //エラーハンドリング
  if (targetString == "") {
    Serial.print("path error ");
    return;
  }
//  Serial.print("Reading file : ");
//  Serial.println(targetString);
  //ファイル名を生成する
  targetString = "/" + targetString;

  File targetFiles = fs.open(targetString);
  if (!file || file.isDirectory()) {
    Serial.println("- failed to open file for reading");
    return;
  }

  int i = 0;
  while (file.available()) {
    //    Serial.write(file.read());
    switch (num) {
      case 0:
        rootCA[i] = file.read();
        break;
      case 1:
        certificate[i] = file.read();
        break;
      case 2:
        privateKey[i] = file.read();
        break;
    }
    i++;
  }

  file.close();
  return;
}