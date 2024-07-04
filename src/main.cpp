#include <Arduino.h>
#include <EEPROM.h>
#include "MyWiFiManager.h"
#include "MyWebServer.h"
#include "RGBController.h"
#include <LittleFS.h>

RGBController rgbController;
MyWiFiManager wifiManager;
MyWebServer webServer;

void setup()
{
    Serial.begin(115200);
    EEPROM.begin(512);
    wifiManager.setup();
    rgbController.begin();
    LittleFS.begin();
    webServer.begin(&rgbController);
}

void loop()
{
    wifiManager.update();
    rgbController.update();
}
