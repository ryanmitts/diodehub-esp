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

#include "Meteor.h"

static const int OVERSHOOT_MULT = 1.5;

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
