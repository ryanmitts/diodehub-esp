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
	WiFiManagerParameter server("server", "Server", Settings::getInstance()->hostname, 65);
    WiFiManagerParameter numLeds("numLeds", "Number of LEDs", Settings::getInstance()->numLeds, 4);

    String ssid = String(ssidPrefix) + (uint32_t)ESP.getEfuseMac();
	WiFi.softAPsetHostname(ssid.c_str());
	wifiManager.setSaveConfigCallback(saveConfigNotifierCallback);
	wifiManager.addParameter(&clientId);
	wifiManager.addParameter(&clientSecret);
	wifiManager.addParameter(&server);
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
		strcpy(Settings::getInstance()->hostname, server.getValue());
		strcpy(Settings::getInstance()->numLeds, numLeds.getValue());
		Settings::getInstance()->saveSettings();
	}


    return true;
}
