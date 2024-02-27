#include <M5Core2.h>
#include "audio.h"
#include <AudioFileSourceSD.h>
#include <AudioGeneratorMP3.h>
#include <AudioOutputI2S.h>

// WiFi設定
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";



void setup() {


  audio_setup();

  //のwhile(1);

}





void loop() {
  // ここでは何もしない

  if (mp3->begin(file, out)) {
    while (mp3->isRunning()) {
      mp3->loop();
    }
    mp3->stop();
  }
  //vTaskDelete(NULL); // Delete the task when done
  //delay(100);
}

