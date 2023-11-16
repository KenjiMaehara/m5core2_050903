#include <HTTPClient.h>
#include <ArduinoJson.h>

extern String gLocationInfo;  // main.cpp など他のファイルで宣言された gLocationInfo を参照
String gCity;

void displayLocation() {
  HTTPClient http;
  http.begin("http://ip-api.com/json/");
  int httpCode = http.GET();

  if (httpCode > 0) {
    String payload = http.getString();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
    String city = doc["city"].as<String>();
    gCity = city;


    // 簡単なマッピングテーブル
    if (city == "Tokyo") {
      gLocationInfo = "東京都";
    } else if (city == "Chiyoda") {
      gLocationInfo = "千代田区";
    } else {
      gLocationInfo = city;  // その他の場合はそのまま表示
    }
  } else {
    gLocationInfo = "Location: Unable to retrieve";
  }

  http.end();
}
