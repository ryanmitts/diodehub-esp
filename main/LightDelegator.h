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
