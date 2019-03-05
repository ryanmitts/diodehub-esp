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
