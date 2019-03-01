#include "Rainbow.h"

static const CRGB RAINBOW_COLORS[7] {
  {255, 0, 0},
  {255, 127, 0},
  {255, 255, 0},
  {0, 255, 0},
  {0, 0, 255},
  {75, 0, 130},
  {148, 0, 211}
};

void Rainbow::start(CRGB* leds, int numLeds) {
    EffectBase::start(leds, numLeds);
    fillRainbow();
}

void Rainbow::start(CRGB* leds, int numLeds, StandardEffect effect, int speed) {
    EffectBase::start(leds, numLeds, effect, speed);
    fillRainbow();
}

void Rainbow::fillRainbow() {
  int numPerColor = floor(numLeds / 7);
  int leftOver = numLeds % 7;
  int startPos = 0;
  int endPos = 0;
  for (int i = 0; i < 6; i++) {
    startPos = i * numPerColor;
    endPos = startPos + numPerColor;
    fill_gradient_RGB(leds, startPos, RAINBOW_COLORS[i], endPos, RAINBOW_COLORS[i + 1]);
  }
  startPos = 6 * numPerColor;
  endPos = startPos + numPerColor + leftOver;
  fill_gradient_RGB(leds, startPos, RAINBOW_COLORS[6], endPos, RAINBOW_COLORS[0]);
}

void Rainbow::looper() {
    EffectBase::looper();
}