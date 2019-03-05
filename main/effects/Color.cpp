/**
 * DiodeHub ESP
 * Copyright (C) 2019 Ryan Mitts
 *
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
