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
  //wav->begin(file, out);

  // audio_taskタスクを作成
  xTaskCreate(audio_task, "AudioTask", 10000, NULL, 1, NULL);
}


// 修正されたaudio_task関数のシグネチャ
void audio_task(void *pvParameters) {
  for(;;) { // 無限ループでタスクを実行
    // Check if Button A is pressed
    if (M5.BtnA.wasPressed()) {
      M5.Lcd.printf("Playing WAV\n");
      Serial.printf("Playing WAV\n");
      if (!wav->isRunning()) {
        wav->begin(file, out);
      }
    }

    // Loop audio playback
    if (wav->isRunning()) {
      if (!wav->loop()) {
        wav->stop();
        M5.Lcd.printf("WAV Playback finished\n");
        Serial.printf("WAV Playback finished\n");
      }
    }
    // Delay a bit to debounce
    //delay(100);
    M5.update();
  }
}
