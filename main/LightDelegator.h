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

#pragma once
#include <string>
#include <string.h>
#include <Arduino.h>
#include <SPI.h>
#include <Base64.h>
#include <FastLED.h>
#include <ArduinoJson.h>
#include "effects/EffectBase.h"
#include "effects/Rainbow.h"
#include "effects/Twinkle.h"
#include "effects/RandomTwinkle.h"
#include "effects/PulseInOut.h"
#include "effects/Meteor.h"
#include "effects/RunningColor.h"
#include "effects/Fire.h"
#include "effects/Color.h"

class LightDelegator {
public:
  static LightDelegator* getInstance(); 
  bool start(int);
	void handleMessage(JsonObject);
  void looper();
private:
  LightDelegator();
  static LightDelegator* instance;
  Color color;
  Fire fire;
  Meteor meteor;
  PulseInOut pulseInOut;
  Rainbow rainbow;
  RandomTwinkle randomTwinkle;
  Twinkle twinkle;
  RunningColor runningColor;
  CRGB *ledBuffer;
  CRGB *colorBuffer;
  int numLeds;
  EffectBase* currentEffect;
  bool fillColorBufferFromArray(JsonArray&);
};
