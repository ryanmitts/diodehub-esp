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

#include "Settings.h"

Settings* Settings::instance = NULL;

Settings::Settings() {
    strcpy(hostname, "diodehub.com");
    strcpy(port, "443");
    strcpy(clientId, "");
    strcpy(clientSecret, "");
}

Settings* Settings::getInstance() {
    if (instance == NULL) {
        instance = new Settings();
    }
    return instance;
}

void Settings::loadSettings()
{
	Serial.println("Loading settings to global.");
	Serial.println("Mounted file system.");
	if (SPIFFS.exists("/config.json"))
	{
		Serial.println("Reading config file.");
		File configFile = SPIFFS.open("/config.json", "r");
		if (configFile)
		{
			Serial.println("Opened config file.");
			size_t size = configFile.size();
			// Allocate a buffer to store contents of the file.
			std::unique_ptr<char[]> buffer(new char[size]);

			configFile.readBytes(buffer.get(), size);
			StaticJsonDocument<512> jsonBuffer;
            DeserializationError err = deserializeJson(jsonBuffer, buffer.get());
            serializeJson(jsonBuffer, Serial);
			if (!err)
			{
				Serial.println("\nParsed json.");

				strcpy(clientId, jsonBuffer["clientId"]);
				strcpy(clientSecret, jsonBuffer["clientSecret"]);
				strcpy(numLeds, jsonBuffer["numLeds"]);
			}
			else
			{
				Serial.println("Failed to load json config.");
			}
			configFile.close();
		}
	}
	else
	{
		Serial.println("Config file does not exist.");
	}
}

void Settings::saveSettings()
{
	Serial.println("Saving settings from global.");
	StaticJsonDocument<512> jsonBuffer;
	jsonBuffer["clientId"] = clientId;
	jsonBuffer["clientSecret"] = clientSecret;
	jsonBuffer["numLeds"] = numLeds;

	File configFile = SPIFFS.open("/config.json", "w");
	if (!configFile)
	{
		Serial.println("Failed to open config file for writing.");
	}

    serializeJson(jsonBuffer, Serial);
    serializeJson(jsonBuffer, configFile);
	configFile.close();
}
