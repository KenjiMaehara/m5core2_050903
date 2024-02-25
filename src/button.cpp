#include <M5Core2.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
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
    if (!client.connected()) {
      //while (!client.connect(gDeviceName.c_str())) {
        delay(1000);
      //}
    }
    M5.update();
    if (M5.BtnB.wasPressed()) {

      String topic = String("button/topic/") + gDeviceName; // トピック名を構築
      if(client.publish(topic.c_str(), (gDeviceName + " Button A was pressed").c_str())){
        Serial.println("Button A press event published to AWS IoT.");
      } else {
        Serial.println("Failed to publish Button A press event.");
      }

      vTaskDelay(100 / portTICK_PERIOD_MS); // 100ミリ秒の遅延
    }
  }
}

