#pragma once

#include <Arduino.h>
#include <FastLED.h>

class EffectBase {
public:
    enum StandardEffect {
        NONE,
        ROTATE_RIGHT,
        ROTATE_LEFT,
        FLASH
    };
    virtual void start(CRGB* leds, int numLeds);
    virtual void start(CRGB* leds, int numLeds, int speed);
    virtual void start(CRGB* leds, int numLeds, StandardEffect effect, int speed);
    virtual void looper();
protected:
    CRGB* leds;
    int numLeds;
    StandardEffect effect;
    int speed;
    unsigned long lastUpdate;
    bool shouldUpdate();
    void setUpdated();
    void rotateRight();
    void rotateLeft();
    void setAllOff();
    void setAllOn();
private:
    CRGB backupLeds[2096];
    bool lastFlashOn;
};
