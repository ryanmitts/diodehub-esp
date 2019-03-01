#pragma once
#include "EffectBase.h"

class Rainbow: public EffectBase {
public:
    void start(CRGB* leds, int numLeds, EffectBase::StandardEffect effect, int speed);
    void start(CRGB* leds, int numLeds);
    void looper();
private:
    void fillRainbow();
};
