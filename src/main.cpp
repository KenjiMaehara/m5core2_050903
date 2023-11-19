//M5stack core2の基本的なプログラム
#include <M5Core2.h>
//wifiのライブラリ
#include <WiFi.h>



void setup() {
  M5.begin();
  M5.Lcd.println("Hello World");
  M5.Spk.begin();  // Initialize the speaker.
  M5.Spk.DingDong();  // Play the DingDong sound.
  delay(100);
}


void loop() {
  M5.update();
  if (M5.BtnA.wasPressed()) {
    M5.Lcd.println("Button A");
    //音を鳴らす
  } else if (M5.BtnB.wasPressed()) {
    M5.Lcd.println("Button B");
    //M5.Spk.tone(2000, 100);  // Play a 2000Hz tone for 100ms.
  } else if (M5.BtnC.wasPressed()) {
    M5.Lcd.println("Button C");
    //M5.Spk.tone(3000, 100);  // Play a 3000Hz tone for 100ms.
    M5.Spk.DingDong();  // Play the DingDong sound.
  }
  delay(100);

}
