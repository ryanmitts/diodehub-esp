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
