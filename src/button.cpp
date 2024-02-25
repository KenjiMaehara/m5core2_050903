#include <M5Core2.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "payload.h"
#include "AWSPub.h"


void buttonTask(void *parameter);
bool sendSignalDataToAWS(const String& jsonPayload);

void buttonsetup() {
  M5.begin();
  // タスクを作成し、実行を開始
  xTaskCreate(buttonTask, "Button Task", 10000, NULL, 1, NULL);
}



static unsigned long lastPressTime = 0;
const unsigned long debounceTime = 1000; // 1秒間のデバウンス時間

// タスクで実行する関数を宣言
void buttonTask(void *parameter) {
  for (;;) { // 無限ループ
    M5.update();
    if (M5.BtnB.wasPressed()) {
      //if (currentTime - lastPressTime > debounceTime) 
      {
        //lastPressTime = currentTime;
        String jsonPayload = createJsonPayload(gDeviceName, "deviceId", "organization", millis(), "sensorValue", "1", "routineCheck", "spare1", "spare2");
        // ここでAWSにjsonPayloadをパブリッシュするコードを実装
        sendSignalDataToAWS(jsonPayload);

        Serial.println("Button B was pressed");
      }
    }
    vTaskDelay(100 / portTICK_PERIOD_MS); // 100ミリ秒の遅延
  }
}


bool sendSignalDataToAWS(const String& jsonPayload) {
  if (!client.connected()) {
    #if 1
    while (!client.connect(gDeviceName.c_str())) {
        delay(1000);
    }
    #endif

    Serial.print("Payload size: ");
    Serial.println(jsonPayload.length()); // ペイロードのサイズを出力
    // 生成されたペイロードをAWS IoTに送信
    if(client.publish("topic/path", jsonPayload.c_str())){
      Serial.println("AWS IoTにSignalデータを送信しました。");
      return true;
    } else {
      Serial.println("AWS IoTへのSignalデータ送信に失敗しました。");
      return false;
    }
  }
}
