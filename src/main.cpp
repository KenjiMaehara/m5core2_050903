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
  // WAVファイルの再生ロジックをここに記述
  // ...
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
