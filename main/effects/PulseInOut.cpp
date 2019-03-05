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

#include "PulseInOut.h"

static const uint8_t PHASE_LENGTH = 0xFF; 
static const int UPDATE_INTERVAL = 20;

void PulseInOut::start(CRGB* leds, int numLeds, CRGB* colors, int numColors, int speed) {
    EffectBase::start(leds, numLeds, UPDATE_INTERVAL);
    this->colors = colors;
    this->numColors = numColors;
    this->currentColorIndex = 0;
    this->currentPhase = 0;
    this->phaseCycleDuration = speed;
    this->startPhaseTime = millis();
    setAllOff();
};

void PulseInOut::looper() {
    if (!shouldUpdate()) return;
    unsigned long start = startPhaseTime;
    unsigned long end = start + phaseCycleDuration;
    unsigned long currentTime = millis();
    if (currentTime >= end) {
        currentPhase = 0x00;
        currentColorIndex++;
        if (currentColorIndex == numColors) currentColorIndex = 0;
        startPhaseTime = currentTime;
    } else {
        float percentOfPhase = (float)(currentTime - start) / phaseCycleDuration;
        currentPhase = percentOfPhase * PHASE_LENGTH;
    }

    uint8_t currentWaveValue = triwave8(currentPhase);
    CRGB currentColor = colors[currentColorIndex];
    CRGB scaledColor = currentColor;
    scaledColor.r = scale8(scaledColor.r, currentWaveValue);
    scaledColor.g = scale8(scaledColor.g, currentWaveValue);
    scaledColor.b = scale8(scaledColor.b, currentWaveValue);
    fill_solid(leds, numLeds, scaledColor);
    setUpdated();
};
