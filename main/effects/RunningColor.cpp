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

#include "RunningColor.h"

static const int OVERSHOOT_MULT = 2;

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
