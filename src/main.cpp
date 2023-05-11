#include <M5Core2.h>
#include <WiFi.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>

const char *configFile = "/wifi_config.json";
const char *ssid;
const char *password;

void loadWifiConfig();
void saveWifiConfig(const char *ssid, const char *password);
void connectToWiFi();


void setup()
{
  M5.begin();
  Serial.begin(115200);

  if (!SPIFFS.begin(true))
  {
    Serial.println("An error occurred while mounting SPIFFS");
    return;
  }

  loadWifiConfig();
  connectToWiFi();
}

void loop()
{
  // WiFi接続後の処理をここに記述

}

void loadWifiConfig()
{
  if (!SPIFFS.exists(configFile))
  {
    Serial.println("WiFi config file not found");
    return;
  }

  File configFile = SPIFFS.open("/config.txt", "r");
  if (!configFile)
  {
    Serial.println("Failed to open WiFi config file");
    return;
  }

  // WiFi設定情報の読み込み
  StaticJsonDocument<256> jsonConfig;
  DeserializationError error = deserializeJson(jsonConfig, configFile);
  if (error)
  {
    Serial.println("Failed to parse WiFi config file");
    return;
  }

  ssid = jsonConfig["ssid"];
  password = jsonConfig["password"];

  configFile.close();
}

void saveWifiConfig(const char *ssid, const char *password)
{
  StaticJsonDocument<256> jsonConfig;
  jsonConfig["ssid"] = ssid;
  jsonConfig["password"] = password;

  File configFile = SPIFFS.open("/config.txt", "w");
  if (!configFile)
  {
    Serial.println("Failed to open WiFi config file for writing");
    return;
  }

  serializeJson(jsonConfig, configFile);
  configFile.close();
}

void connectToWiFi()
{
  if (!ssid || !password)
  {
    Serial.println("No WiFi config available");
    return;
  }

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected to WiFi");
}
