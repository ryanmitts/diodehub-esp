#pragma once

#include <Arduino.h>
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
    static bool checkAndUpdate();
private:
    static String currentVersion;
    static String currentMd5;
    static String getUpdateLocation();
};
