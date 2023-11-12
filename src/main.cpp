#include <M5Core2.h>
#include <driver/i2s.h>
#include "AudioFileSourceSD.h"
#include "AudioGeneratorWAV.h"
//#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"

#include "VButton.h"

AudioGeneratorWAV *wav = NULL;
//AudioGeneratorMP3 *mp3 = NULL;
AudioFileSourceSD *file;
AudioOutputI2S *out;

#define BCLK_PIN 12
#define LRCK_PIN 0
#define SADTA_PIN 2
#define EXTERNAL_I2S 0
#define OUTPUT_GAIN 80

VButton * button_bach;
VButton * button_beethoven;
VButton * button_chopin;

uint16_t getColor(uint8_t red, uint8_t green, uint8_t blue){
  return ((red>>3)<<11) | ((green>>2)<<5) | (blue>>3);
}

void button_callback(char *name, bool use_toggle, bool is_toggled){
	char path[128];
	
	// 再生中の場合は、停止する
	if(wav != NULL){
		wav->stop();
	}
	
	sprintf(path,"/%s.wav",name);
	file = new AudioFileSourceSD(path);
	out = new AudioOutputI2S(I2S_NUM_0, EXTERNAL_I2S); 
	out->SetPinout(BCLK_PIN, LRCK_PIN, SADTA_PIN);
	out->SetOutputModeMono(true);
	out->SetGain((float)OUTPUT_GAIN/100.0);
	wav = new AudioGeneratorWAV();
	wav->begin(file, out);
}

void setup() {
	M5.begin();
	M5.Lcd.setBrightness(255);
	M5.Lcd.fillScreen(WHITE);
	// スピーカーの初期化
	M5.Axp.SetSpkEnable(true); 
	// 操作ボタン
	ushort dark_gray = getColor(80, 80, 80);
	button_bach = new VButton("sample1", button_callback, false, -70, dark_gray);  
	button_beethoven = new VButton("sample2", button_callback, false, 0, dark_gray);  
	button_chopin = new VButton("sample3", button_callback, false, 70, dark_gray);  
}

void loop() {
	button_bach->loop();
	button_beethoven->loop();
	button_chopin->loop();

	if(wav != NULL){
		if (wav->isRunning()) {
			if (!wav->loop()) wav->stop();
		} else {
			Serial.printf("WAV done\n");
			delay(1000);
		}
	}
}