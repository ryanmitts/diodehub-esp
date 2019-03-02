#include "Setup.h"

const char ssidPrefix[] = "DiodeHub-";

bool shouldSaveConfig = false;

void saveConfigNotifierCallback()
{
	shouldSaveConfig = true;
}

bool Setup::start() {
    Settings::getInstance()->loadSettings();
    WiFiManager wifiManager;
    WiFiManagerParameter clientId("clientId", "Client ID", Settings::getInstance()->clientId, 65, "autocomplete=\"off\" autocorrect=\"off\" autocapitalize=\"off\"");
    WiFiManagerParameter clientSecret("clientSecret", "Client Secret", Settings::getInstance()->clientSecret, 65, "type=\"password\"");
    WiFiManagerParameter numLeds("numLeds", "Number of LEDs", Settings::getInstance()->numLeds, 4);

    String ssid = String(ssidPrefix) + (uint32_t)ESP.getEfuseMac();
	WiFi.softAPsetHostname(ssid.c_str());
	wifiManager.setSaveConfigCallback(saveConfigNotifierCallback);
	wifiManager.addParameter(&clientId);
	wifiManager.addParameter(&clientSecret);
	wifiManager.addParameter(&numLeds);
	if (!wifiManager.autoConnect(ssid.c_str()))
	{
		Serial.println("WiFiManager could not connect.");
		return false;
	}

    if (shouldSaveConfig)
	{
		strcpy(Settings::getInstance()->clientId, clientId.getValue());
		strcpy(Settings::getInstance()->clientSecret, clientSecret.getValue());
		strcpy(Settings::getInstance()->numLeds, numLeds.getValue());
		Settings::getInstance()->saveSettings();
	}


    return true;
}
