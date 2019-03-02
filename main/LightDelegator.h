#pragma once
#include <string>
#include <string.h>
#include <Arduino.h>
#include <SPI.h>
#include "Callback.h"
#include <Base64CString.h>
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
	LightDelegator();
  bool start(int);
	void handleMessage(JsonObject);
  void looper();
private:
  int numLeds;
  EffectBase* currentEffect;
};
