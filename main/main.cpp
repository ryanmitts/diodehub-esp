#include <FS.h>
#include <SPIFFS.h>
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include <ArduinoJson.h>
#include <Callback.h>
#include "MessageHttpClient.h"
#include "LightDelegator.h"
#include "UpdateHandler.h"
#include <esp_ota_ops.h>

static const char ssidPrefix[] = "DiodeHub-";

char HOSTNAME[65] = "diodehub.com";
char PORT[6] = "443";
char CLIENT_ID[65] = "";
char CLIENT_SECRET[65] = "";
char NUM_LEDS[6] = "";

WiFiManagerParameter hostname("hostname", "Server Hostname", HOSTNAME, 65, "autocomplete=\"off\" autocorrect=\"off\" autocapitalize=\"off\"");
WiFiManagerParameter port("port", "Server Port", PORT, 6);
WiFiManagerParameter clientId("clientId", "Client ID", CLIENT_ID, 65, "autocomplete=\"off\" autocorrect=\"off\" autocapitalize=\"off\"");
WiFiManagerParameter clientSecret("clientSecret", "Client Secret", CLIENT_SECRET, 65, "type=\"password\"");
WiFiManagerParameter numLeds("numLeds", "Number of LEDs", NUM_LEDS, 4);

bool shouldSaveConfig = false;
bool servicesStarted = false;

MessageHttpClient messageClient;
LightDelegator lightDelegator;
MethodSlot<LightDelegator, JsonObject &> onMessageSlot(&lightDelegator, &LightDelegator::handleMessage);

// Read out the stored settings from the flash memory for use.
void loadSettingsToGlobal()
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
			DynamicJsonBuffer jsonBuffer;
			JsonObject &json = jsonBuffer.parseObject(buffer.get());
			json.printTo(Serial);
			if (json.success())
			{
				Serial.println("\nParsed json.");

				strcpy(HOSTNAME, json["hostname"]);
				strcpy(PORT, json["port"]);
				strcpy(CLIENT_ID, json["clientId"]);
				strcpy(CLIENT_SECRET, json["clientSecret"]);
				strcpy(NUM_LEDS, json["numLeds"]);
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

void saveSettingsFromGlobal()
{
	Serial.println("Saving settings from global.");
	DynamicJsonBuffer jsonBuffer;
	JsonObject &json = jsonBuffer.createObject();
	json["hostname"] = HOSTNAME;
	json["port"] = PORT;
	json["clientId"] = CLIENT_ID;
	json["clientSecret"] = CLIENT_SECRET;
	json["numLeds"] = NUM_LEDS;

	File configFile = SPIFFS.open("/config.json", "w");
	if (!configFile)
	{
		Serial.println("Failed to open config file for writing.");
	}

	json.printTo(Serial);
	json.printTo(configFile);
	configFile.close();
}

void saveConfigNotifierCallback()
{
	shouldSaveConfig = true;
}

bool startServices()
{
	bool messageClientStarted = messageClient.start(HOSTNAME, PORT, CLIENT_ID, CLIENT_SECRET);
	bool lightDelegatorStarted = lightDelegator.start(atoi(NUM_LEDS));
	return messageClientStarted && lightDelegatorStarted;
}

void coreZeroLoop(void *parameters)
{
	while (true)
	{
		if (servicesStarted)
		{
			messageClient.looper();
		}
	}
}

void loop()
{
	if (servicesStarted)
	{
		lightDelegator.looper();
	}
	delay(1000);
}

void setup()
{
	Serial.begin(115200);
	Serial.println("Setup starting.");
	Serial.println("DiodeHub Version:");
	Serial.println(UpdateHandler::getCurrentVersion());
	Serial.println("Sketch MD5");
	Serial.println(UpdateHandler::getCurrentMd5());

	randomSeed(analogRead(36));

	Serial.println("Mounting file system.");
	bool fsMounted = SPIFFS.begin();
	if (!fsMounted)
	{
		Serial.println("Mounting failed, creating.");
		SPIFFS.begin(true);
	}

	loadSettingsToGlobal();

	String ssid = String(ssidPrefix) + (uint32_t)ESP.getEfuseMac();
	WiFi.softAPsetHostname(ssid.c_str());
	WiFiManager wifiManager;
	wifiManager.setSaveConfigCallback(saveConfigNotifierCallback);
	wifiManager.addParameter(&hostname);
	wifiManager.addParameter(&port);
	wifiManager.addParameter(&clientId);
	wifiManager.addParameter(&clientSecret);
	wifiManager.addParameter(&numLeds);
	if (!wifiManager.autoConnect(ssid.c_str()))
	{
		Serial.println("WiFiManager could not connect.");
		delay(3000);
		ESP.restart();
		delay(5000);
	}

	Serial.println("Connected.");

	configTime(0, 0, "pool.ntp.org", "time.nist.gov");
	Serial.print(F("Waiting for NTP time sync: "));
	time_t now = time(nullptr);
	while (now < 8 * 3600 * 2)
	{
		delay(20);
		Serial.print(F("."));
		now = time(nullptr);
	}
	Serial.println("");

	if (shouldSaveConfig)
	{
		strcpy(HOSTNAME, hostname.getValue());
		strcpy(PORT, port.getValue());
		strcpy(CLIENT_ID, clientId.getValue());
		strcpy(CLIENT_SECRET, clientSecret.getValue());
		strcpy(NUM_LEDS, numLeds.getValue());
		saveSettingsFromGlobal();
	}

	servicesStarted = startServices();

	xTaskCreatePinnedToCore(
		coreZeroLoop,		   /* Function to implement the task */
		"messageClientLooper", /* Name of the task */
		10000,				   /* Stack size in words */
		NULL,				   /* Task input parameter */
		0,					   /* Priority of the task */
		NULL,				   /* Task handle. */
		0);					   /* Core where the task should run */

	Serial.println("Boot setup ran.");
}
