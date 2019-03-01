#include "LightDelegator.h"

static const int LED_BUFFER_SIZE = 2096;
static const int LED_PIN = 12;
static const int BRIGHTNESS = 128;
static const std::string NUM_SIGN = "#";

CRGB ledBuffer[LED_BUFFER_SIZE];
CRGB colorBuffer[LED_BUFFER_SIZE * 3];

Color color;
Fire fire;
Meteor meteor;
PulseInOut pulseInOut;
Rainbow rainbow;
RandomTwinkle randomTwinkle;
Twinkle twinkle;
RunningColor runningColor;

LightDelegator::LightDelegator() {
    pinMode(LED_PIN, OUTPUT);
};

bool LightDelegator::start(int numLeds) {
   this->numLeds = numLeds;
   FastLED.addLeds<WS2812B, LED_PIN, GRB>(ledBuffer, numLeds).setCorrection(TypicalLEDStrip);
   FastLED.setBrightness(BRIGHTNESS);
   Serial.println("Light delegator started.");
   return true;
}

void LightDelegator::looper() {
    if (currentEffect != NULL) {
        currentEffect->looper();
    }
    delay(1);
    FastLED.show();
}

int64_t parseInt(const std::string& str, uint8_t base = 10) {
    return strtoll(str.c_str(), nullptr, base);
}

// https://github.com/mapbox/css-color-parser-cpp/blob/master/csscolorparser.cpp
CRGB parseColor(const std::string& color) {
    std::string str = color;

    // Remove all whitespace, not compliant, but should just be more accepting.
    str.erase(std::remove(str.begin(), str.end(), ' '), str.end());

    // Convert to lowercase.
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);

    // #abc and #abc123 syntax.
    if (str.length() && str.front() == '#') {
        if (str.length() == 4) {
            int64_t iv = parseInt(str.substr(1), 16);  // TODO(deanm): Stricter parsing.
            if (!(iv >= 0 && iv <= 0xfff)) {
                return CRGB();
            } else {
                return CRGB(
                    static_cast<uint8_t>(((iv & 0xf00) >> 4) | ((iv & 0xf00) >> 8)),
                    static_cast<uint8_t>((iv & 0xf0) | ((iv & 0xf0) >> 4)),
                    static_cast<uint8_t>((iv & 0xf) | ((iv & 0xf) << 4))
                );
            }
        } else if (str.length() == 7) {
            int64_t iv = parseInt(str.substr(1), 16);  // TODO(deanm): Stricter parsing.
            if (!(iv >= 0 && iv <= 0xffffff)) {
                return CRGB();
            } else {
                return CRGB(
                    static_cast<uint8_t>((iv & 0xff0000) >> 16),
                    static_cast<uint8_t>((iv & 0xff00) >> 8),
                    static_cast<uint8_t>(iv & 0xff)
                );
            }
        }
    }

    return CRGB();
}

bool fillColorBufferFromArray(JsonArray& colors) {
    int size = colors.size();
    bool passed = true;
    for (int i = 0; i < size; i++) {
        const char* colorCodeCString = colors.get<char*>(i);
        if (colorCodeCString == NULL) {
            passed = false;
            break;
        }
        std::string colorCode(colorCodeCString);
        colorBuffer[i] = parseColor(colorCode);
    }

    return passed;
}

void LightDelegator::handleMessage(JsonObject& message) {
    Serial.println("Got light message to send");
    const char* effect = message.get<char*>("effect");
    if (effect == NULL) return;
    if (strcmp(effect, "color") == 0) {
        JsonVariant colors = message.get<JsonVariant>("colors");
        if (!colors.is<JsonArray>()) return;
        JsonArray& colorsArray = colors.as<JsonArray>();
        if (colorsArray.size() > LED_BUFFER_SIZE * 3) return;
        if (!fillColorBufferFromArray(colorsArray)) return;
        int numColors = colors.size();

        bool effectStarted = false;
        JsonVariant options = message.get<JsonVariant>("options");
        if (options.is<JsonObject>()) {
            JsonObject& optionsObject = options.as<JsonObject>();
            if (optionsObject.containsKey("subEffect")) {
                const char* subEffect = optionsObject.get<char*>("subEffect");
                int speed = optionsObject.get<int>("speed");
                if (speed > 0) {
                    if (strcmp(subEffect, "rotateRight") == 0) {
                        color.start(ledBuffer, numLeds, colorBuffer, numColors, EffectBase::StandardEffect::ROTATE_RIGHT, speed);
                        effectStarted = true;
                    } else if (strcmp(subEffect, "rotateLeft") == 0) {
                        color.start(ledBuffer, numLeds, colorBuffer, numColors, EffectBase::StandardEffect::ROTATE_LEFT, speed);
                        effectStarted = true;
                    } else if (strcmp(subEffect, "flash") == 0) {
                        color.start(ledBuffer, numLeds, colorBuffer, numColors, EffectBase::StandardEffect::FLASH, speed);
                        effectStarted = true;
                    }
                }
            }
        };

        if (!effectStarted) {
            color.start(ledBuffer, numLeds, colorBuffer, numColors);
        }
        currentEffect = &color;
    } else if (strcmp(effect, "fire") == 0) {
        JsonVariant options = message.get<JsonVariant>("options");
        int cooling = 50;
        int sparking = 120;
        int speed = 20;
        if (options.is<JsonObject>()) {
            JsonObject& optionsObject = options.as<JsonObject>();
            if (optionsObject.containsKey("cooling")) cooling = optionsObject.get<int>("cooling");
            if (optionsObject.containsKey("sparking")) sparking = optionsObject.get<int>("sparking");
            if (optionsObject.containsKey("speed")) speed = optionsObject.get<int>("speed");
        };
        fire.start(ledBuffer, numLeds, cooling, sparking, speed);
        currentEffect = &fire;
    } else if (strcmp(effect, "meteor") == 0) {
        // Repeated, move out;
        JsonVariant colors = message.get<JsonVariant>("colors");
        JsonArray& colorsArray = colors.as<JsonArray>();
        if (colorsArray.size() > LED_BUFFER_SIZE * 3) return;
        if (!fillColorBufferFromArray(colorsArray)) {
            colorBuffer[0] = CRGB::Red;
        };

        JsonVariant options = message.get<JsonVariant>("options");
        int meteorSize = 10;
        int meteorTailDecay = 64;
        int speed = 20;
        if (options.is<JsonObject>()) {
            JsonObject& optionsObject = options.as<JsonObject>();
            if (optionsObject.containsKey("meteorSize")) meteorSize = optionsObject.get<int>("meteorSize");
            if (optionsObject.containsKey("meteorTailDecay")) meteorTailDecay = optionsObject.get<int>("meteorTailDecay");
            if (optionsObject.containsKey("speed")) speed = optionsObject.get<int>("speed");
        };

        meteor.start(ledBuffer, numLeds, colorBuffer[0], meteorSize, meteorTailDecay, speed);
        currentEffect = &meteor;
    } else if (strcmp(effect, "pulseInOut") == 0) {
        // Repeated, move out;
        JsonVariant colors = message.get<JsonVariant>("colors");
        if (!colors.is<JsonArray>()) return;
        JsonArray& colorsArray = colors.as<JsonArray>();
        if (colorsArray.size() > LED_BUFFER_SIZE * 3) return;
        if (!fillColorBufferFromArray(colorsArray)) return;
        int numColors = colors.size();

        JsonVariant options = message.get<JsonVariant>("options");
        int speed = 100;
        if (options.is<JsonObject>()) {
            JsonObject& optionsObject = options.as<JsonObject>();
            if (optionsObject.containsKey("speed")) speed = optionsObject.get<int>("speed");
        };
        pulseInOut.start(ledBuffer, numLeds, colorBuffer, numColors, speed);
        currentEffect = &pulseInOut;
    } else if (strcmp(effect, "rainbow") == 0) {
        bool effectStarted = false;
        JsonVariant options = message.get<JsonVariant>("options");
        if (options.is<JsonObject>()) {
            JsonObject& optionsObject = options.as<JsonObject>();
            if (optionsObject.containsKey("subEffect")) {
                const char* subEffect = optionsObject.get<char*>("subEffect");
                int speed = optionsObject.get<int>("speed");
                if (speed > 0) {
                    if (strcmp(subEffect, "rotateRight") == 0) {
                        rainbow.start(ledBuffer, numLeds, EffectBase::StandardEffect::ROTATE_RIGHT, speed);
                        effectStarted = true;
                    } else if (strcmp(subEffect, "rotateLeft") == 0) {
                        rainbow.start(ledBuffer, numLeds, EffectBase::StandardEffect::ROTATE_LEFT, speed);
                        effectStarted = true;
                    } else if (strcmp(subEffect, "flash") == 0) {
                        rainbow.start(ledBuffer, numLeds, EffectBase::StandardEffect::FLASH, speed);
                        effectStarted = true;
                    }
                }
            }
        };

        if (!effectStarted) {
            rainbow.start(ledBuffer, numLeds);
        }
        currentEffect = &rainbow;
    } else if (strcmp(effect, "randomTwinkle") == 0) {
        JsonVariant options = message.get<JsonVariant>("options");
        int speed = 100;
        if (options.is<JsonObject>()) {
            JsonObject& optionsObject = options.as<JsonObject>();
            if (optionsObject.containsKey("speed")) speed = optionsObject.get<int>("speed");
        };
        randomTwinkle.start(ledBuffer, numLeds, speed);
        currentEffect = &randomTwinkle;
    } else if (strcmp(effect, "twinkle") == 0) {
        // Repeated, move out;
        JsonVariant colors = message.get<JsonVariant>("colors");
        if (!colors.is<JsonArray>()) return;
        JsonArray& colorsArray = colors.as<JsonArray>();
        if (colorsArray.size() > LED_BUFFER_SIZE * 3) return;
        if (!fillColorBufferFromArray(colorsArray)) return;

        JsonVariant options = message.get<JsonVariant>("options");
        int speed = 100;
        if (options.is<JsonObject>()) {
            JsonObject& optionsObject = options.as<JsonObject>();
            if (optionsObject.containsKey("speed")) speed = optionsObject.get<int>("speed");
        };
        twinkle.start(ledBuffer, numLeds, colorBuffer[0], speed);
        currentEffect = &twinkle;
    } else if (strcmp(effect, "runningColor") == 0) {
        // Repeated, move out;
        JsonVariant colors = message.get<JsonVariant>("colors");
        if (!colors.is<JsonArray>()) return;
        JsonArray& colorsArray = colors.as<JsonArray>();
        if (colorsArray.size() > LED_BUFFER_SIZE * 3) return;
        if (!fillColorBufferFromArray(colorsArray)) return;

        JsonVariant options = message.get<JsonVariant>("options");
        int speed = 100;
        if (options.is<JsonObject>()) {
            JsonObject& optionsObject = options.as<JsonObject>();
            if (optionsObject.containsKey("speed")) speed = optionsObject.get<int>("speed");
        };
        runningColor.start(ledBuffer, numLeds, colorBuffer[0], speed);
        currentEffect = &runningColor;
    }
}
