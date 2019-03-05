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
