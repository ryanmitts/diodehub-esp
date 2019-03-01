#pragma once
#include "EffectBase.h"

class RandomTwinkle: public EffectBase {
public:
    void start(CRGB *leds, int numLeds, int speed);
    void looper();
private:
    bool isOn;
    unsigned long lastOnTime;
};
