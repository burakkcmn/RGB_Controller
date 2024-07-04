#include "MyWiFiManager.h"
#include <ESP8266WiFi.h>
#include <EEPROM.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "ESP8266_AP";
const char* password = "12345678";
AsyncWebServer apServer(80);

void MyWiFiManager::setup() {
    Serial.begin(115200);
    EEPROM.begin(512);

    // Read saved WiFi credentials from EEPROM
    char storedSSID[32] = {0};
    char storedPassword[32] = {0};
    EEPROM.get(0, storedSSID);
    EEPROM.get(32, storedPassword);

    if (strlen(storedSSID) > 0) {
        WiFi.begin(storedSSID, storedPassword);
        unsigned long startAttemptTime = millis();
        while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 5000) {
            delay(100);
        }
    }

    if (WiFi.status() != WL_CONNECTED) {
        startAP();
    }
}

void MyWiFiManager::update() {
    // Handle AP server if in AP mode
    //apServer.handleClient();
}

bool MyWiFiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void MyWiFiManager::startAP() {
    WiFi.softAP(ssid, password);

    apServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        request->send(200, "text/html", "<form action='/save' method='POST'>SSID: <input type='text' name='ssid'><br>Password: <input type='password' name='password'><br><input type='submit' value='Save'></form>");
    });

    apServer.on("/save", HTTP_POST, [](AsyncWebServerRequest *request){
        String ssid = request->getParam("ssid", true)->value();
        String password = request->getParam("password", true)->value();
        EEPROM.put(0, ssid.c_str());
        EEPROM.put(32, password.c_str());
        EEPROM.commit();
        request->send(200, "text/plain", "Credentials saved, rebooting...");
        delay(1000);
        ESP.restart();
    });

    apServer.begin();
}
