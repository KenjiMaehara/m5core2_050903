#include "FS.h"
#include "SPIFFS.h"
#include "SPIFFSRead.h"


String SPIFFSRead::readFirstFileWithExtension(const String &extension) {
    if (!SPIFFS.begin(true)) {
        Serial.println("SPIFFSのマウントに失敗しました。");
        return "";
    }

    File root = SPIFFS.open("/");
    File file = root.openNextFile();
    while (file) {
        String fileName = file.name();
        if (fileName.endsWith(extension)) {
            Serial.println("読み込み中: " + fileName);
            String fileContent;
            while (file.available()) {
                fileContent += (char)file.read();
            }
            file.close();
            return fileContent;
        }
        file = root.openNextFile();
    }
    return ""; // ファイルが見つからなかった場合
}