#pragma once
#include "EffectBase.h"

class Fire: public EffectBase {
public:
    void start(CRGB *leds, int numLeds, int cooling, int sparking, int speed);
    void looper();
private:
    int cooling;
    int sparking;
    void setPixelHeatColor (int ledNum, byte temperature);
    byte heat[2096];
};
