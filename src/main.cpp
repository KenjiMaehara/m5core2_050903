#include <M5Core2.h>
#include <FS.h>
#include <SD.h>

void setup() {
  // M5Stack Core2の初期化
  M5.begin();

  // SDカードの初期化
  if (!SD.begin()) {
    Serial.println("SD Card Mount Failed");
    return;
  }

  // ボタンの配置
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE, BLACK);
  M5.Lcd.drawCentreString("Button 1", 80, 100, 4);
  M5.Lcd.drawCentreString("Button 2", 160, 100, 4);
  M5.Lcd.drawCentreString("Button 3", 240, 100, 4);
}

void playWavFile(const char *filename) {
  // WAVファイルを開く
  File file = SD.open(filename, FILE_READ);

  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  // WAVファイルのヘッダー等を読み飛ばし、音声データ部分に移動する
  // （この部分はファイル形式によって異なります）

  // 音声データを読み込んで再生する
  // ここに具体的な再生処理を記述
  // ...

  file.close();
}

void loop() {
  // M5Stack Core2の更新
  M5.update();

  // 各ボタンのチェック
  if (M5.BtnA.wasPressed()) {
    playWavFile("/sound1.wav");
  } else if (M5.BtnB.wasPressed()) {
    playWavFile("/sound2.wav");
  } else if (M5.BtnC.wasPressed()) {
    playWavFile("/sound3.wav");
  }
}
