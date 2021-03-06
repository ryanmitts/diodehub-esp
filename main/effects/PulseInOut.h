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

#pragma once
#include "EffectBase.h"

// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects

class PulseInOut: public EffectBase {
public:
    void start(CRGB* leds, int numLeds, CRGB* colors, int numColors, int speed);
    void looper();
private:
    CRGB* colors;
    int numColors;
    int phaseCycleDuration;
    uint8_t currentPhase;
    int currentColorIndex;
    unsigned long startPhaseTime;
};
