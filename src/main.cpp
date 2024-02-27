#include <M5Core2.h>
#include <AudioFileSourceSD.h>
#include <AudioGeneratorMP3.h>
#include <AudioOutputI2S.h>

// WiFi設定
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

AudioGeneratorMP3 *mp3;
AudioFileSourceSD *file;
AudioOutputI2S *out;

void audio_setup();

#define OUTPUT_GAIN 10

void setup() {

  audio_setup();

}



void audio_setup() {
  M5.begin();

  M5.Axp.SetSpkEnable(true);

  out = new AudioOutputI2S(0, 1); // I2Sデータピンとクロックピンを指定
  out->SetPinout(12, 0, 2);
  //out->SetGain(0.3); // 音量を設定
  out->SetOutputModeMono(true);
  out->SetGain((float)OUTPUT_GAIN/100.0);
  file = new AudioFileSourceSD("/test.mp3"); // SDカードのルートにあるMP3ファイル
  mp3 = new AudioGeneratorMP3();

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

