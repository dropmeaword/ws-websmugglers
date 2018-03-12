#define SPIFFS_ALIGNED_OBJECT_INDEX_TABLES 1

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <FS.h>
#include <WiFiClient.h>
#include <TimeLib.h>
#include <NtpClientLib.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266mDNS.h>
#include <Ticker.h>
#include <ArduinoOTA.h>
#include <ArduinoJson.h>
#include <FSWebServerLib.h>
#include <Hash.h>

#define SPIFFS_ALIGNED_OBJECT_INDEX_TABLES 1


bool wifi_connect_as_client(const char *ssid, const char *passw, int timeouts = 10) {
  boolean succeeded = true;

  WiFi.mode(WIFI_STA);  // both hotspot and client are enabled
  WiFi.begin(ssid, passw);
  Serial.println("Connecting to WiFi ");
  Serial.println(ssid);
  //LOG_NEW_LINE

  // wait for connection
  Serial.println("Connecting");
  unsigned long tout = millis() + (timeouts * 1000);
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
    if (millis() > tout) {
      succeeded = false;
      break;
    }
  }
  //LOG_NEW_LINE

  // if we are connected we probably were assigned an IP
  if (succeeded) {
    // thisip = WiFi.localIP();
    // // copy assigned IP to config
    // config.cfg_ip[0] = thisip[0];
    // config.cfg_ip[1] = thisip[1];
    // config.cfg_ip[2] = thisip[2];
    // config.cfg_ip[3] = thisip[3];
  }

  //config.cfg_mode = WifiMode::CLIENT;

  return succeeded;
}


void setup() {
  Serial.begin(115200);
  //wifi_connect_as_client("CABO_VERDE", "12345678");

  Serial.println();
  Serial.println();
  
  // WiFi is started inside library
  if(SPIFFS.begin()) {
    Serial.println(">>> SPIFFS initialized successfully");
  }

  if(SPIFFS.exists("/config.json")) {
    Serial.println("(@@) config.json found");
  } else {
    Serial.println("(!!) config.json missing!");
  }
  Serial.println();

  Dir dir = SPIFFS.openDir("/");
  Serial.println("SPIFFS directory {/} :");
  while (dir.next()) {
      Serial.print(" "); Serial.println(dir.fileName());
      Serial.println(" "); Serial.println(dir.fileSize());
  }
  Serial.println();
  Serial.println();


  delay(1000);
  ESPHTTPServer.begin(&SPIFFS);
}

void loop() {
    // DO NOT REMOVE. Attend OTA update from Arduino IDE
    ESPHTTPServer.handle();  
    delay(20);
}

