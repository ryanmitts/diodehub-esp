#include "RunningColor.h"

static const int OVERSHOOT_MULT = 2;

// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects

void RunningColor::start(CRGB* leds, int numLeds, CRGB color, int speed) {
    EffectBase::start(leds, numLeds, speed);
    this->currentPos = 0;
    this->color = color;
    setAllOff();
}

void RunningColor::looper() {
    if (!shouldUpdate()) return;

    currentPos++;
    if (currentPos == (numLeds * OVERSHOOT_MULT)) currentPos = 0;

    for (int i = 0; i < numLeds; i++) {
        double multiplier = (sin(i + currentPos) * 127 + 128) / 255;
        leds[i].r = multiplier * color.r;
        leds[i].g = multiplier * color.g;
        leds[i].b = multiplier * color.b;
    }

    setUpdated();
}
