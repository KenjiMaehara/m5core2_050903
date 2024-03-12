#include <M5Core2.h>
#include <WiFi.h>
#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

//const char ssid[] = "YourSSID";
//const char pass[] = "YourPassword";
const char thingId[] = "YourDeviceID"; // Device IDをここに追加
const char thingPsw[] = "YourSecretKey"; // Secret Keyをここに追加

void cloudTask(void *pvParameters) {
  (void) pvParameters;

  while (1) {
    ArduinoCloud.update();
    vTaskDelay(1000 / portTICK_PERIOD_MS); // 1秒ごとにArduino Cloudを更新
  }
}

void arduinoCloud_setup() {
  Serial.begin(9600);
  //M5.begin();
  //WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  ArduinoCloud.setThingId(thingId);
  ArduinoCloud.setThingPassword(thingPsw);

  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  xTaskCreatePinnedToCore(
    cloudTask,              // タスクの関数
    "CloudTask",            // タスクの名前
    8192,                   // スタックサイズ（バイト単位）
    NULL,                   // タスクパラメータ
    1,                      // タスクの優先度
    NULL,                   // タスクハンドラ
    1                       // コア番号（0または1）
  );
}

