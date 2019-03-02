#pragma once

#include <FS.h>
#include <SPIFFS.h>
#include <Arduino.h>
#include <ArduinoJson.h>

class Settings {
public:
    static Settings* getInstance();
    char hostname[65];
    char port[6];
    char clientId[65];
    char clientSecret[65];
    char numLeds[6];
    void loadSettings();
    void saveSettings();
private:
    static Settings* instance;
    Settings();
};
