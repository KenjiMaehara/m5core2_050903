// SPIFFSRead.h
#ifndef SPIFFSRead_h
#define SPIFFSRead_h

#include "FS.h"
#include "SPIFFS.h"
#include <string>

class SPIFFSRead {
public:
    static String readFirstFileWithExtension(const String &extension);
};

#endif