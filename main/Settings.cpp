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
