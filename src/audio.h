#ifndef AUDIO_H
#define AUDIO_H

#include <AudioFileSourceSD.h>
#include <AudioGeneratorMP3.h>
#include <AudioOutputI2S.h>

void audio_setup();

extern AudioGeneratorMP3 *mp3;
extern AudioFileSourceSD *file;
extern AudioOutputI2S *out;

#endif // AUDIO_H