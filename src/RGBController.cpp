#include "RGBController.h"

void RGBController::begin()
{
    // Initialize the pins as OUTPUT
    for (int i = 0; i < 3; ++i)
    {
        pinMode(redPins[i], OUTPUT);
        pinMode(greenPins[i], OUTPUT);
        pinMode(bluePins[i], OUTPUT);
    }
    clearAll();
}

void RGBController::setColor(uint8_t channel, uint8_t red, uint8_t green, uint8_t blue)
{
    if (channel < 3)
    {
        applyColor(channel, red, green, blue);
    }
}

void RGBController::setBrightness(uint8_t channel, uint8_t newBrightness)
{
    if (channel < 3)
    {
        brightness[channel] = newBrightness;
        // Re-apply the current color with the new brightness
    }
}

void RGBController::setAnimation(uint8_t animationId)
{
    currentAnimation = animationId;
    animationStartTime = millis();
}

void RGBController::update()
{
    switch (currentAnimation)
    {
    case 1:
        animationRainbow();
        break;
    case 2:
        animationBlink();
        break;
    case 3:
        animationPulse();
        break;
    case 4:
        animationChase();
        break;
    case 5:
        animationFade();
        break;
    case 6:
        animationSparkle();
        break;
    case 7:
        animationStrobe();
        break;
    case 8:
        animationWave();
        break;
    case 9:
        animationMeteor();
        break;
    case 10:
        animationColorCycle();
        break;
    default:
        break;
    }
}

void RGBController::applyColor(uint8_t channel, uint8_t red, uint8_t green, uint8_t blue)
{
    analogWrite(redPins[channel], map(red * brightness[channel] / 255, 0, 255, 0, 1023));
    analogWrite(greenPins[channel], map(green * brightness[channel] / 255, 0, 255, 0, 1023));
    analogWrite(bluePins[channel], map(blue * brightness[channel] / 255, 0, 255, 0, 1023));
}

void RGBController::clearAll()
{
    for (int i = 0; i < 3; ++i)
    {
        applyColor(i, 0, 0, 0);
    }
}

// Animation functions
void RGBController::animationRainbow()
{
    uint32_t now = millis();
    uint8_t pos = (now / 10) % 255;

    for (int i = 0; i < 3; ++i)
    {
        uint8_t red = sin(pos + (i * 85)) * 127 + 128;
        uint8_t green = sin(pos + (i * 85) + 85) * 127 + 128;
        uint8_t blue = sin(pos + (i * 85) + 170) * 127 + 128;
        applyColor(i, red, green, blue);
    }
}

void RGBController::animationBlink()
{
    uint32_t now = millis();
    uint8_t value = (now / 500) % 2 ? 255 : 0;

    for (int i = 0; i < 3; ++i)
    {
        applyColor(i, value, value, value);
    }
}

void RGBController::animationPulse()
{
    uint32_t now = millis();
    uint8_t value = (sin(now / 500.0 * 3.14) * 127 + 128);

    for (int i = 0; i < 3; ++i) {
        applyColor(i, value, value, value);
    }
}

void RGBController::animationChase()
{
    uint32_t now = millis();
    uint8_t pos = (now / 100) % 3;

    for (int i = 0; i < 3; ++i) {
        if (i == pos) {
            applyColor(i, 255, 255, 255);
        } else {
            applyColor(i, 0, 0, 0);
        }
    }
}

void RGBController::animationFade()
{
    uint32_t now = millis();
    uint8_t value = (sin(now / 1000.0 * 3.14) * 127 + 128);

    for (int i = 0; i < 3; ++i) {
        applyColor(i, value, 0, 0);
    }
}

void RGBController::animationSparkle()
{
    static uint32_t lastChange = 0;
    if (millis() - lastChange > 100) {
        lastChange = millis();
        uint8_t channel = random(3);
        uint8_t red = random(256);
        uint8_t green = random(256);
        uint8_t blue = random(256);
        applyColor(channel, red, green, blue);
    }
}

void RGBController::animationStrobe()
{
    uint32_t now = millis();
    uint8_t value = (now / 50) % 2 ? 255 : 0;

    for (int i = 0; i < 3; ++i) {
        applyColor(i, value, value, value);
    }
}

void RGBController::animationWave()
{
    uint32_t now = millis();
    uint8_t pos = (now / 100) % 255;

    for (int i = 0; i < 3; ++i) {
        uint8_t red = sin(pos + (i * 85)) * 127 + 128;
        uint8_t green = sin(pos + (i * 85) + 85) * 127 + 128;
        uint8_t blue = sin(pos + (i * 85) + 170) * 127 + 128;
        applyColor(i, red, green, blue);
    }
}

void RGBController::animationMeteor()
{
    uint32_t now = millis();
    uint8_t pos = (now / 50) % 3;

    for (int i = 0; i < 3; ++i) {
        if (i == pos) {
            applyColor(i, 255, 255, 255);
        } else {
            applyColor(i, 0, 0, 0);
        }
    }
}

void RGBController::animationColorCycle()
{
    uint32_t now = millis();
    uint8_t red = (sin(now / 1000.0 * 3.14) * 127 + 128);
    uint8_t green = (sin(now / 1000.0 * 3.14 + 2) * 127 + 128);
    uint8_t blue = (sin(now / 1000.0 * 3.14 + 4) * 127 + 128);

    for (int i = 0; i < 3; ++i) {
        applyColor(i, red, green, blue);
    }
}
