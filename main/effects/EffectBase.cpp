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

#include "EffectBase.h"

void EffectBase::start(CRGB* leds, int numLeds) {
    this->leds = leds;
    this->numLeds = numLeds;
    this->effect = StandardEffect::NONE;
}

void EffectBase::start(CRGB* leds, int numLeds, int speed) {
    this->leds = leds;
    this->numLeds = numLeds;
    this->speed = speed;
    this->effect = StandardEffect::NONE;
}

void EffectBase::start(CRGB* leds, int numLeds, StandardEffect effect, int speed) {
    this->leds = leds;
    this->numLeds = numLeds;
    this->effect = effect;
    this->speed = speed;
    this->lastFlashOn = true;
}

void EffectBase::rotateRight() {
    CRGB last = leds[numLeds - 1];
    for (int i = (numLeds - 1); i > 0; i--) {
        leds[i] = leds[i - 1];
    }
    leds[0] = last;
}

void EffectBase::rotateLeft() {
    CRGB first = leds[0];
    for (int i = 0; i < (numLeds - 1); i ++) {
        leds[i] = leds[i + 1];
    }
    leds[numLeds - 1] = first;
}

void EffectBase::setAllOff() {
    for (int i = 0; i < numLeds; i++) {
        backupLeds[i] = leds[i];
        leds[i] = CRGB::Black;
    }
}

void EffectBase::setAllOn() {
    for (int i = 0; i < numLeds; i++) {
        leds[i] = backupLeds[i];
    }
}

bool EffectBase::shouldUpdate() {
    unsigned long currentTime = millis();
    return (currentTime - lastUpdate) > speed;
}

void EffectBase::setUpdated() {
    lastUpdate = millis();
}

void EffectBase::looper() {
    if (!shouldUpdate()) return;
    if (effect == EffectBase::StandardEffect::ROTATE_LEFT) {
        rotateLeft();
    } else if (effect == EffectBase::StandardEffect::ROTATE_RIGHT) {
        rotateRight();
    } else if (effect == EffectBase::StandardEffect::FLASH) {
        if (lastFlashOn) {
            setAllOff();
            lastFlashOn = false;
        } else {
            setAllOn();
            lastFlashOn = true;
        }
    }
    setUpdated();
}
