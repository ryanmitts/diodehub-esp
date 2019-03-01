#pragma once
#include "EffectBase.h"

class Twinkle: public EffectBase {
public:
    void start(CRGB *leds, int numLeds, CRGB color, int speed);
    void looper();
private:
    CRGB color;
    bool isOn;
    unsigned long lastOnTime;
};
