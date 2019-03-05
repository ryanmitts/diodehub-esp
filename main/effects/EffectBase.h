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

#include <Arduino.h>
#include <FastLED.h>

class EffectBase {
public:
    enum StandardEffect {
        NONE,
        ROTATE_RIGHT,
        ROTATE_LEFT,
        FLASH
    };
    virtual void start(CRGB* leds, int numLeds);
    virtual void start(CRGB* leds, int numLeds, int speed);
    virtual void start(CRGB* leds, int numLeds, StandardEffect effect, int speed);
    virtual void looper();
protected:
    CRGB* leds;
    int numLeds;
    StandardEffect effect;
    int speed;
    unsigned long lastUpdate;
    bool shouldUpdate();
    void setUpdated();
    void rotateRight();
    void rotateLeft();
    void setAllOff();
    void setAllOn();
private:
    CRGB backupLeds[2096];
    bool lastFlashOn;
};
