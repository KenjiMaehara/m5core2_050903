#include <ArduinoJson.h> // JSON操作のためのライブラリをインクルード
#include "payload.h" // ヘッダーファイルをインクルード

// JSONペイロードを作成する関数
String createJsonPayload(
  const String& deviceName, 
  const String& deviceId, 
  const String& organization, 
  unsigned long timestamp, 
  const String& sensor, 
  const String& button, 
  const String& routineCheck, 
  const String& spare1, 
  const String& spare2
  ) {
  StaticJsonDocument<512> jsonDoc; // JSONドキュメントを作成
  
  // データをJSONドキュメントに追加
  jsonDoc["deviceName"] = deviceName;
  jsonDoc["deviceId"] = deviceId;
  jsonDoc["organization"] = organization;
  jsonDoc["timestamp"] = timestamp;
  jsonDoc["sensor"] = sensor;
  jsonDoc["button"] = button;
  jsonDoc["routineCheck"] = routineCheck;
  #if 1
  jsonDoc["spare1"] = spare1;
  jsonDoc["spare2"] = spare2;
  #endif

  String payload;
  serializeJson(jsonDoc, payload); // JSONオブジェクトを文字列に変換

  return payload; // 作成したペイロードを返す
}
