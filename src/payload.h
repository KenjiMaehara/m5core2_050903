#ifndef PAYLOAD_H
#define PAYLOAD_H

#include <Arduino.h>

// ペイロード作成関数のプロトタイプ宣言
//String createJsonPayload(String deviceName, String deviceId, String organization, unsigned long timestamp, String sensor, String button, String routineCheck, String spare1, String spare2);
String createJsonPayload(const String& deviceName, const String& deviceId, const String& organization, unsigned long timestamp, const String& sensor, const String& button, const String& routineCheck, const String& spare1, const String& spare2);

#endif // PAYLOAD_H
