/**
 * DiodeHub ESP
 * Copyright (C) 2019 Ryan Mitts

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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