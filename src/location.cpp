#include <HTTPClient.h>
#include <ArduinoJson.h>

extern String locationInfo;  // main.cpp など他のファイルで宣言された locationInfo を参照

void displayLocation() {
  HTTPClient http;
  http.begin("http://ip-api.com/json/");
  int httpCode = http.GET();

  if (httpCode > 0) {
    String payload = http.getString();
    DynamicJsonDocument doc(1024);
    deserializeJson(doc, payload);
    String city = doc["city"].as<String>();


    // 簡単なマッピングテーブル
    if (city == "Tokyo") {
      locationInfo = "東京都";
    } else if (city == "Chiyoda") {
      locationInfo = "千代田区";
    } else {
      locationInfo = city;  // その他の場合はそのまま表示
    }
  } else {
    locationInfo = "Location: Unable to retrieve";
  }

  http.end();
}
