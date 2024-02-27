#include <M5Core2.h>
#include <driver/i2s.h>
#include "AudioFileSourceSD.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2S.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


AudioGeneratorWAV *wav;
AudioFileSourceSD *file;
AudioOutputI2S *out;

#define OUTPUT_GAIN 200

void audio_task(void *pvParameters);


void audio_setup()
{
  M5.begin();
  M5.Axp.SetSpkEnable(true);

  delay(500);
  
  M5.Lcd.setTextFont(2);
  M5.Lcd.printf("Sample WAV playback begins...\n");
  Serial.printf("Sample WAV playback begins...\n");

  file = new AudioFileSourceSD("/test.wav");
  out = new AudioOutputI2S(0, 0); // Output to ExternalDAC
  out->SetPinout(12, 0, 2);
  out->SetOutputModeMono(true);
  out->SetGain((float)OUTPUT_GAIN/100.0);
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);

  // audio_taskタスクを作成
  xTaskCreate(audio_task, "AudioTask", 10000, NULL, 1, NULL);
}


// 修正されたaudio_task関数のシグネチャ
void audio_task(void *pvParameters) {
  for(;;) { // 無限ループでタスクを実行
    if (wav->isRunning()) {
      if (!wav->loop()) wav->stop();
    } else {
      Serial.printf("WAV done\n");
      vTaskDelay(1000 / portTICK_PERIOD_MS); // 1秒待機
    }
  }
}
