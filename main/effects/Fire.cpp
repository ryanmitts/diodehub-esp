#include "Fire.h"

static const int OVERSHOOT_MULT = 2;

// https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects

void Fire::start(CRGB* leds, int numLeds, int cooling, int sparking, int speed) {
    EffectBase::start(leds, numLeds, speed);
    this->cooling = cooling;
    this->sparking = sparking;
}

void Fire::setPixelHeatColor (int ledNum, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature / 255.0) * 191);
 
  // calculate ramp up from
  byte heatRamp = t192 & 0x3F; // 0..63
  heatRamp <<= 2; // scale up to 0..252
 
  // figure out which third of the spectrum we're in:
  if (t192 > 0x80) {                     // hottest
    leds[ledNum].r = 255;
    leds[ledNum].g = 255;
    leds[ledNum].b = heatRamp;
  } else if (t192 > 0x40) {             // middle
    leds[ledNum].r = 255;
    leds[ledNum].g = heatRamp;
    leds[ledNum].b = 0;
  } else {                               // coolest
    leds[ledNum].r = heatRamp;
    leds[ledNum].g = 0;
    leds[ledNum].b = 0;
  }
}

void Fire::looper() {
    if (!shouldUpdate()) return;

    int cooldown;
    
    // Step 1.  Cool down every cell a little
    for (int i = 0; i < numLeds; i++) {
        cooldown = random(0, ((cooling * 10) / numLeds) + 2);
        
        if (cooldown > heat[i]) {
            heat[i] = 0;
        } else {
            heat[i] = heat[i] - cooldown;
        }
    }
    
    // Step 2.  Heat from each cell drifts 'up' and diffuses a little
    for (int k = numLeds - 1; k >= 2; k--) {
        heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
    }
        
    // Step 3.  Randomly ignite new 'sparks' near the bottom
    if (random(255) < sparking ) {
        int y = random(7);
        heat[y] = heat[y] + random(160,255);
    }

    // Step 4.  Convert heat to LED colors
    for (int j = 0; j < numLeds; j++) {
        setPixelHeatColor(j, heat[j]);
    }

    setUpdated();
}
