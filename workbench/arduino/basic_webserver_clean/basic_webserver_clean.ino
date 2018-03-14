

#include <Arduino.h>
#include <ESP8266WiFi.h>
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

#include "config.h"
#include "log.h"
#include "wifi.h"
#include "filesystem.h"



void setup() {
  Serial.begin(115200);
  
  // WiFi is started inside library
  if(!SPIFFS.begin()) {
    Serial.println("(!!) SPIFFS failed to initialize");
  }

  if(SPIFFS.exists("/config.json")) {
    Serial.println("(--) config.json found");
  } else {
    Serial.println("(!!) config.json missing!");
  }
  Serial.println();


//  if( wifi_connect_as_client(wifi_ssid, wifi_password, 10) ) {
//    LOG("Connected to ");
//    LOG(wifi_ssid);
//    LOG("IP address: ");
//  }

  wifi_create_ap("mesh_001");
  Serial.println();
  Serial.println();
  
  // list contents of flash memory
  fs_list_dir("/");
  // separator
  Serial.println();
  Serial.println();

  delay(1000);
  ESPHTTPServer.begin(&SPIFFS);
}

void loop() {
    // DO NOT REMOVE. Attend OTA update from Arduino IDE
    ESPHTTPServer.handle();  
    delay(50);
}

