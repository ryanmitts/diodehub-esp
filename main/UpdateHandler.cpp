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

#include "UpdateHandler.h"

extern const uint8_t ca_certificates_pem_start[] asm("_binary_ca_certificates_pem_start");
extern const uint8_t ca_certificates_pem_end[] asm("_binary_ca_certificates_pem_end");

String UpdateHandler::currentVersion = "";
String UpdateHandler::currentMd5 = "";

String UpdateHandler::getCurrentVersion() {
    if (!UpdateHandler::currentVersion.length()) {
        const esp_app_desc_t *appDesc = esp_ota_get_app_description();
        UpdateHandler::currentVersion = String(appDesc->version);
    }

    return UpdateHandler::currentVersion;
}

String UpdateHandler::getCurrentMd5() {
    if (!UpdateHandler::currentMd5.length()) {
        UpdateHandler::currentMd5 = ESP.getSketchMD5();
    }

    return UpdateHandler::currentMd5;
}

String UpdateHandler::getUpdateLocation() {
    WiFiClientSecure client;
    client.setCACert((const char *)ca_certificates_pem_start);
    HTTPClient httpClient;
    if (!httpClient.begin(client, Config::UPDATE_URL)) {
        Serial.println("Could not connect to update check server.");
        return "";
    }
    String currentHash = ESP.getSketchMD5();
    httpClient.addHeader("x-esp32-md5", UpdateHandler::getCurrentMd5());
    httpClient.addHeader("x-esp32-version", UpdateHandler::getCurrentVersion());
    Serial.println("Current sketch hash:");
    Serial.println(UpdateHandler::getCurrentMd5());
    int statusCode = httpClient.GET();
    if (statusCode == HTTP_CODE_OK) {
        Serial.println("There is an update, will download.");
        return httpClient.getString();
    } else if (statusCode == HTTP_CODE_NO_CONTENT) {
        Serial.println("No update.");
        return "";
    } else {
        Serial.println("Failed to check for update.");
        return "";
    }
}

bool UpdateHandler::checkAndUpdate()
{
    Serial.println("");
    String updateLocation = getUpdateLocation();
    if (updateLocation.length() == 0) {
        return true;
    }

    WiFiClientSecure client;
    client.setCACert((const char *)ca_certificates_pem_start);
    HTTPClient httpClient;
    if (!httpClient.begin(client, updateLocation)) {
        Serial.println("Could not connect to update firmware location.");
    }

    const char * headerKeys[] = { "x-amz-meta-md5" };
    size_t headerKeysSize = sizeof(headerKeys) / sizeof(char*);
    httpClient.collectHeaders(headerKeys, headerKeysSize);

    int statusCode = httpClient.GET();
    int contentLength = httpClient.getSize();
    Serial.println("HTTP Status:");
    Serial.println(statusCode);
    Serial.println("Content length:");
    Serial.println(contentLength);

    if (statusCode != HTTP_CODE_OK) {
        Serial.println("Could not retrieve update file.");
        return false;
    }

    int freeParitionSize = ESP.getFreeSketchSpace();
    Serial.printf("Free partition size %d.\n", freeParitionSize);
    if (contentLength > freeParitionSize) {
        Serial.println("Not enough free space.");
        return false;
    }

    WiFiClient *stream = httpClient.getStreamPtr();
    int command = U_FLASH;

    if (!Update.begin(contentLength, command)) {
        Serial.println("Not enough space for the update");
        return false;
    }
    String md5 = httpClient.header("x-amz-meta-md5");
    Serial.println("New firmware image MD5:");
    Serial.println(md5);
    if (md5.length()) {
        if (!Update.setMD5(md5.c_str())) {
            Serial.println("Could not set MD5 from update server response.");
            return false;
        }
        Serial.println("Will use md5 hash to verify update.");
    }
    // Get MD5 from headers and check it.
    Serial.println("Updating....");
    int writeSize = Update.writeStream(*stream);
    if (writeSize != contentLength) {
        Serial.println("Update write length did not match firmware download size.");
    }
    Serial.println("Ending update.");
    int finishedUpdate = Update.end();
    if (finishedUpdate) {
        Serial.println("Finished update.");
        return true;
    } else {
        Serial.println("Did not finish update.");
    }
  
    return false;
}
