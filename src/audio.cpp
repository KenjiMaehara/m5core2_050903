#include <M5Core2.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <AudioFileSourceSD.h>
#include <AudioGeneratorMP3.h>
#include <AudioOutputI2S.h>

// Forward declaration of the task function
void PlayMP3Task(void *parameter);

AudioGeneratorMP3 *mp3;
AudioFileSourceSD *file;
AudioOutputI2S *out;

void audio_setup() {
  M5.begin();
  // Create a task that will execute the PlayMP3Task() function, with a name of "PlayMP3"
  xTaskCreatePinnedToCore(PlayMP3Task, "PlayMP3", 10000, NULL, 1, NULL, 0);
}


void PlayMP3Task(void *parameter) {
  out = new AudioOutputI2S(0, 1); // I2Sデータピンとクロックピンを指定
  out->SetGain(0.125); // 音量を設定
  file = new AudioFileSourceSD("/test.mp3"); // SDカードのルートにあるMP3ファイル
  mp3 = new AudioGeneratorMP3();
  if (mp3->begin(file, out)) {
    while (mp3->isRunning()) {
      mp3->loop();
    }
    mp3->stop();
  }
  vTaskDelete(NULL); // Delete the task when done
}
