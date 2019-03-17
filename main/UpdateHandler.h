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
#include <ArduinoJson.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <Update.h>
#include "Config.h"
#include <esp_ota_ops.h>

class UpdateHandler {
public:
    static String getCurrentVersion();
    static String getCurrentMd5();
    static bool update(JsonObject message);
private:
    static String currentVersion;
    static String currentMd5;
};
