#pragma once
#include "EffectBase.h"

class PulseInOut: public EffectBase {
public:
    void start(CRGB* leds, int numLeds, CRGB* colors, int numColors, int speed);
    void looper();
private:
    CRGB* colors;
    int numColors;
    int phaseCycleDuration;
    uint8_t currentPhase;
    int currentColorIndex;
    unsigned long startPhaseTime;
};
