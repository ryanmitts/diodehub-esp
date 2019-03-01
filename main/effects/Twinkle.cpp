#include "Twinkle.h"

static const unsigned long ON_LENGTH = 100;

void Twinkle::start(CRGB* leds, int numLeds, CRGB color, int speed) {
    EffectBase::start(leds, numLeds, speed);
    this->color = color;
    this->isOn = false;
    setAllOff();
}

void Twinkle::looper() {
    if (!shouldUpdate()) {
        if (isOn && (lastOnTime + ON_LENGTH > millis())) {
            isOn = false;
            setAllOff();
        }
        return;
    }
    setAllOff();
    long whatLight = random(numLeds);
    leds[whatLight] = color;
    isOn = true;
    lastOnTime = millis();
    setUpdated();
}
