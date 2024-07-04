#ifndef RGBCONTROLLER_H
#define RGBCONTROLLER_H

#include <Arduino.h>

class RGBController {
public:
    void begin();
    void setColor(uint8_t channel, uint8_t red, uint8_t green, uint8_t blue);
    void setBrightness(uint8_t channel, uint8_t brightness);
    void setAnimation(uint8_t animationId);
    void update();  // Call this in the main loop to handle animations

private:
    const uint8_t redPins[3] = {D1, D4, D7};     // R1, R2, R3
    const uint8_t greenPins[3] = {D2, D5, D8};   // G1, G2, G3
    const uint8_t bluePins[3] = {D3, D6, D9};    // B1, B2, B3
    uint8_t brightness[3] = {255, 255, 255};     // Brightness for each channel

    uint8_t currentAnimation = 0;
    unsigned long animationStartTime;
    void applyColor(uint8_t channel, uint8_t red, uint8_t green, uint8_t blue);
    void clearAll();

    // Animation functions
    void animationRainbow();
    void animationBlink();
    void animationPulse();
    void animationChase();
    void animationFade();
    void animationSparkle();
    void animationStrobe();
    void animationWave();
    void animationMeteor();
    void animationColorCycle();
};

#endif // RGBCONTROLLER_H
