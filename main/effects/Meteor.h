#pragma once
#include "EffectBase.h"

class Meteor: public EffectBase {
public:
    void start(CRGB* leds, int numLeds, CRGB color, int meteorSize, int meteorTailDecay, int speed);
    void looper();
private:
    CRGB color;
    int meteorSize;
    int meteorTailDecay;
    int currentPos;
};
