#include "RandomTwinkle.h"

static const unsigned long ON_LENGTH = 100;

void RandomTwinkle::start(CRGB* leds, int numLeds, int speed) {
    EffectBase::start(leds, numLeds, speed);
    this->isOn = false;
    setAllOff();
}

void RandomTwinkle::looper() {
    if (!shouldUpdate()) {
        if (isOn && (lastOnTime + ON_LENGTH > millis())) {
            isOn = false;
            setAllOff();
        }
        return;
    }
    setAllOff();
    long whatLight = random(numLeds);
    leds[whatLight].r = random(0,255);
    leds[whatLight].g = random(0,255);
    leds[whatLight].b = random(0,255);
    isOn = true;
    lastOnTime = millis();
    setUpdated();
}
