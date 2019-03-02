#include <FS.h>
#include <SPIFFS.h>
#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <Callback.h>
#include "MessageHttpClient.h"
#include "LightDelegator.h"
#include "UpdateHandler.h"
#include "Settings.h"
#include "Setup.h"

static const int MESSAGE_BUFFER_SIZE = 8192;
static const char LIGHTS_MESSAGE_EVENT[] = "lights";

StaticJsonDocument<MESSAGE_BUFFER_SIZE> jsonMessageBuffer;
TaskHandle_t xMessageClientTask = NULL;
TaskHandle_t xLightMessageReceiverTask = NULL;
TaskHandle_t xLightHandlerTask = NULL;
QueueHandle_t xLightMessageQueue = xQueueCreate(1, sizeof(JsonDocument*));

bool servicesStarted = false;

LightDelegator lightDelegator;

bool startServices()
{
	return true;
}


void loop()
{
	if (servicesStarted)
	{
		lightDelegator.looper();
	}
	delay(1000);
}

void messageClientTask(void *parameter) {
	MessageHttpClient messageClient;
	messageClient.start(Settings::getInstance()->hostname, Settings::getInstance()->port, Settings::getInstance()->clientId, Settings::getInstance()->clientSecret);
	for (;;) {
		messageClient.checkAndPerformHeartbeat();
		bool hasMessage = messageClient.checkAndReceiveMessage(&jsonMessageBuffer);
		if (hasMessage) {
			const char *eventName = jsonMessageBuffer[0];
			Serial.println("Event name:");
			Serial.println(eventName);
			if (strcmp(eventName, LIGHTS_MESSAGE_EVENT) == 0) {
				JsonDocument *pointerToMessage = &jsonMessageBuffer;
				if (xQueueSendToBack(xLightMessageQueue, (void *) &pointerToMessage, 0) == pdFALSE) {
					Serial.println("Could not place light message in it's queue.");
				} else {
					Serial.println("Going to wait for the light message to be handled.");
					ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
					jsonMessageBuffer.clear();
				}

			}
		}
		vTaskDelay(pdMS_TO_TICKS( 500 ));
	}
}

void lightMessageReceiverTask(void *parameters) {
	lightDelegator.start(atoi(Settings::getInstance()->numLeds));
	JsonDocument *message;
	for (;;) {
		if (xQueueReceive(xLightMessageQueue, &(message), portMAX_DELAY)) {
			Serial.println("Handled light message");
			lightDelegator.handleMessage((*message)[1]);
			xTaskNotifyGive(xMessageClientTask);
		}
	}
}

void lightUpdaterTask(void *parameters) {
	for (;;) {
		lightDelegator.looper();
		vTaskDelay(pdMS_TO_TICKS( 5 ));
	}
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

	bool connected = Setup::start();
	if (!connected) {
		Serial.println("Could not connect tp WiFi or run setup.");
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

	// servicesStarted = startServices();

	xTaskCreatePinnedToCore(
		messageClientTask,		   /* Function to implement the task */
		"messageClientTask", /* Name of the task */
		10000,				   /* Stack size in words */
		NULL,				   /* Task input parameter */
		configMAX_PRIORITIES / 2,					   /* Priority of the task */
		&xMessageClientTask,				   /* Task handle. */
		tskNO_AFFINITY);					   /* Core where the task should run */

	xTaskCreatePinnedToCore(
		lightMessageReceiverTask,		   /* Function to implement the task */
		"lightMessageReceiverTask", /* Name of the task */
		10000,				   /* Stack size in words */
		NULL,				   /* Task input parameter */
		configMAX_PRIORITIES / 2,					   /* Priority of the task */
		&xLightMessageReceiverTask,				   /* Task handle. */
		tskNO_AFFINITY);					   /* Core where the task should run */
	
	xTaskCreatePinnedToCore(
		lightUpdaterTask,		   /* Function to implement the task */
		"lightUpdaterTask", /* Name of the task */
		10000,				   /* Stack size in words */
		NULL,				   /* Task input parameter */
		configMAX_PRIORITIES / 2,					   /* Priority of the task */
		&xLightHandlerTask,				   /* Task handle. */
		tskNO_AFFINITY);					   /* Core where the task should run */

	Serial.println("Boot setup ran.");
}
