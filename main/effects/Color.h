#pragma once
#include "EffectBase.h"

class Color: public EffectBase {
public:
    void start(CRGB* leds, int numLeds, CRGB* colors, int numColors, EffectBase::StandardEffect effect, int speed);
    void start(CRGB* leds, int numLeds, CRGB* colors, int numColors);
    void looper();
private:
    CRGB* colors;
    int numColors;
    void fillWithColors();
};
