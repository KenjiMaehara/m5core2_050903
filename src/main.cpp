#include <M5Core2.h>
#include <driver/i2s.h>
#include <WiFi.h>
#include "AudioFileSourceSD.h"
#include "AudioGeneratorWAV.h"
#include "AudioOutputI2S.h"
#include "audio.h"


void setup()
{
  audio_setup();

}

void loop()
{
  delay(100);
}