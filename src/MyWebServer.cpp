#include "MyWebServer.h"
#include <ESPAsyncWebServer.h>
#include <LittleFS.h>

AsyncWebServer server(80);
RGBController* rgbControllerPtr;

void handleRoot(AsyncWebServerRequest *request) {
    request->send(LittleFS, "/index.html", "text/html");
}

void handleControl(AsyncWebServerRequest *request) {
    request->send(LittleFS, "/control.html", "text/html");
}

void handleSetColor(AsyncWebServerRequest *request) {
    if (request->hasParam("channel") && request->hasParam("color") && request->hasParam("brightness")) {
        int channel = request->getParam("channel")->value().toInt();
        uint32_t color = strtoul(request->getParam("color")->value().c_str(), nullptr, 16);
        uint8_t red = (color >> 16) & 0xFF;
        uint8_t green = (color >> 8) & 0xFF;
        uint8_t blue = color & 0xFF;
        uint8_t brightness = request->getParam("brightness")->value().toInt();
        rgbControllerPtr->setColor(channel, red, green, blue);
        rgbControllerPtr->setBrightness(channel, brightness);
        request->send(200, "text/plain", "Color Set");
    } else {
        request->send(400, "text/plain", "Invalid Request");
    }
}

void handleSetAnimation(AsyncWebServerRequest *request) {
    if (request->hasParam("animation")) {
        int animationId = request->getParam("animation")->value().toInt();
        rgbControllerPtr->setAnimation(animationId);
        request->send(200, "text/plain", "Animation Set");
    } else {
        request->send(400, "text/plain", "Invalid Request");
    }
}

void MyWebServer::begin(RGBController* controller) {
    rgbControllerPtr = controller;
    if(!LittleFS.begin()){
        Serial.println("An error has occurred while mounting LittleFS");
        return;
    }

    server.on("/", HTTP_GET, handleRoot);
    server.on("/control", HTTP_GET, handleControl);
    server.on("/set_color", HTTP_POST, handleSetColor);
    server.on("/set_animation", HTTP_POST, handleSetAnimation);

    server.begin();
}
