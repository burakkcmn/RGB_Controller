#ifndef MYWIFIMANAGER_H
#define MYWIFIMANAGER_H

#include <Arduino.h>

class MyWiFiManager {
public:
    void setup();
    void update();
    bool isConnected();

private:
    void startAP();
    void connectToWiFi();
};

#endif // MYWIFIMANAGER_H
