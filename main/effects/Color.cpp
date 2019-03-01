#include "Color.h"

void Color::start(CRGB* leds, int numLeds, CRGB* colors, int numColors, EffectBase::StandardEffect effect, int speed) {
    EffectBase::start(leds, numLeds, effect, speed);
    this->colors = colors;
    this->numColors = numColors;
    fillWithColors();
}

void Color::start(CRGB* leds, int numLeds, CRGB* colors, int numColors) {
    EffectBase::start(leds, numLeds);
    this->colors = colors;
    this->numColors = numColors;
    fillWithColors();
}

void Color::fillWithColors() {
    int division = floor(numLeds / numColors);
    int leftOver = numLeds % numColors;
    for (int i = 0; i < numColors; i++) {
        int start = i * division;
        int end = start + division - 1;
        // Throw left over lights at the end chunk.
        if (i == numColors - 1) end += leftOver;
        // +1 b/c the second arg is for how many to fill starting at and
        // including the first arg.
        fill_solid(leds + start, end - start + 1, colors[i]);
    }
}

void Color::looper() {
    EffectBase::looper();
}
