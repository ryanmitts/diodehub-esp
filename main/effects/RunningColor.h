#pragma once
#include "EffectBase.h"

class RunningColor: public EffectBase {
public:
    void start(CRGB *leds, int numLeds, CRGB color, int speed);
    void looper();
private:
    CRGB color;
    int currentPos;
};
