#ifndef AUDIO_H
#define AUDIO_H

#include "AudioFileSourceSD.h"
#include "AudioGeneratorWAV.h"

void audio_setup();

extern AudioGeneratorWAV *wav;
extern AudioFileSourceSD *file;

#endif