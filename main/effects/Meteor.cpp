#include "Meteor.h"

static const int OVERSHOOT_MULT = 1.5;

// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects
void Meteor::start(CRGB* leds, int numLeds, CRGB color, int meteorSize, int meteorTailDecay, int speed) {
    EffectBase::start(leds, numLeds, speed);
    this->color = color;
    this->meteorSize = meteorSize;
    this->meteorTailDecay = meteorTailDecay;
    this->currentPos = 0;
    setAllOff();
};

void Meteor::looper() {
    if (!shouldUpdate()) return;

    currentPos++;
    if (currentPos == (numLeds * OVERSHOOT_MULT)) currentPos = 0;

    // fade brightness all LEDs one step
    for (int j = 0; j < numLeds; j++) {
        if (random(10) > 5) {
            leds[j].fadeToBlackBy(meteorTailDecay);     
        }
    }
    
    // draw meteor
    for (int j = 0; j < meteorSize; j++) {
        if ( ( currentPos - j < numLeds) && (currentPos - j >= 0) ) {
            leds[currentPos - j] = color;
        } 
    }

    setUpdated();
};
