#ifndef MYWEBSERVER_H
#define MYWEBSERVER_H

#include <Arduino.h>
#include "RGBController.h"

class MyWebServer {
public:
    void begin(RGBController* controller);
};

#endif // MYWEBSERVER_H
