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

#include <FS.h>
#include <SPIFFS.h>
#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include <nvs_flash.h>
#include <driver/gpio.h>
#include "MessageHttpClient.h"
#include "LightDelegator.h"
#include "UpdateHandler.h"
#include "Settings.h"
#include "Setup.h"

extern "C" {
   void app_main();
}

static const gpio_num_t RESET_PIN = GPIO_NUM_14;

static const int MESSAGE_BUFFER_SIZE = 8192;
static const char LIGHTS_MESSAGE_EVENT[] = "lights";
static const char UPDATE_MESSAGE_EVENT[] = "update";

StaticJsonDocument<MESSAGE_BUFFER_SIZE> jsonMessageBuffer;
TaskHandle_t xMessageClientTask = NULL;
TaskHandle_t xLightMessageReceiverTask = NULL;
TaskHandle_t xLightHandlerTask = NULL;
QueueHandle_t xLightMessageQueue = xQueueCreate(1, sizeof(JsonDocument*));
QueueHandle_t xUpdateMessageQueue = xQueueCreate(1, sizeof(JsonDocument*));
SemaphoreHandle_t xLightControllerLock = xSemaphoreCreateMutex();
xQueueHandle gpioEventQueue = xQueueCreate(10, sizeof(uint32_t));
portMUX_TYPE xLockOnInterrupts = portMUX_INITIALIZER_UNLOCKED;

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
			JsonDocument *pointerToMessage = &jsonMessageBuffer;
			if (strcmp(eventName, LIGHTS_MESSAGE_EVENT) == 0) {
				if (xQueueSendToBack(xLightMessageQueue, (void *) &pointerToMessage, 0) == pdFALSE) {
					Serial.println("Could not place light message in it's queue.");
				} else {
					Serial.println("Going to wait for the light message to be handled.");
					ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
					jsonMessageBuffer.clear();
				}

			} else if (strcmp(eventName, UPDATE_MESSAGE_EVENT) == 0) {
				if (xQueueSendToBack(xUpdateMessageQueue, (void *) &pointerToMessage, 0) == pdFALSE) {
					Serial.println("Could not place update message in it's queue.");
				} else {
					Serial.println("Going to wait for the update message to be handled.");
					ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
					jsonMessageBuffer.clear();
				}
			}
		}
		vTaskDelay(pdMS_TO_TICKS( 500 ));
	}
}

void lightMessageReceiverTask(void *parameters) {
	if (xSemaphoreTake(xLightControllerLock, portMAX_DELAY) == pdTRUE) {
		Serial.println("MR obtained lock.");
		LightDelegator::getInstance()->start(atoi(Settings::getInstance()->numLeds));
		Serial.printf("MR address of LD is %p\n", (void *)LightDelegator::getInstance());  
		Serial.println("MR giving lock.");
		xSemaphoreGive(xLightControllerLock);
	}
	JsonDocument *message;
	for (;;) {
		if (xQueueReceive(xLightMessageQueue, &(message), portMAX_DELAY)) {
			Serial.println("Handled light message");
			if (xSemaphoreTake(xLightControllerLock, portMAX_DELAY) == pdTRUE) {\
				Serial.println("MR obtained lock.");
				LightDelegator::getInstance()->handleMessage((*message)[1]);
				Serial.println("MR giving lock.");
				xSemaphoreGive(xLightControllerLock);
				xTaskNotifyGive(xMessageClientTask);
			} else {
				Serial.println("Light message receiver could not obtain lock on light controller.");
			}
		}
	}
}

void lightUpdaterTask(void *parameters) {
	for (;;) {
		if (xSemaphoreTake(xLightControllerLock, portMAX_DELAY) == pdTRUE) {
			LightDelegator::getInstance()->looper();
			xSemaphoreGive(xLightControllerLock);
		} else {
			Serial.println("Light updater could not obtain lock on light controller.");
		}
		vTaskDelay(pdMS_TO_TICKS( 1 ));
	}
}

void printFreeHeapTask(void *parameters) {
	for (;;) {
		Serial.println("Free heap:");
		Serial.println(ESP.getFreeHeap());
		vTaskDelay(pdMS_TO_TICKS( 5000 ));
	}
}

void checkAndHandleReset() {
	int level = gpio_get_level(RESET_PIN);
	if (level == 0) {
		WiFi.disconnect(true, true);
		vTaskDelay(pdMS_TO_TICKS( 500 ));
		ESP.restart();
	}
}

void gpioInterruptHandlerTask(void *parameter) {
	uint32_t gpioNum;
    for (;;) {
        if (xQueueReceive(gpioEventQueue, &gpioNum, portMAX_DELAY)) {
			if (gpioNum == RESET_PIN) checkAndHandleReset();
        }
    }
}

static void IRAM_ATTR gpioInterruptHandler(void* arg)
{
    uint32_t gpioNum = (uint32_t)arg;
    xQueueSendFromISR(gpioEventQueue, &gpioNum, NULL);
}

void waitForUpdateTask(void *parameter) {
	for (;;) {
		JsonDocument *message;
        if (xQueueReceive(xUpdateMessageQueue, &(message), portMAX_DELAY)) {
			bool res = UpdateHandler::checkAndUpdate();
			if (res) {
				Serial.println("Updated.");
				ESP.restart();
			} else {
				Serial.println("Did not update.");
			}
			xTaskNotifyGive(xMessageClientTask);
        }
    }
}

void app_main()
{
	Serial.begin(115200);
	ESP_ERROR_CHECK( nvs_flash_init() );
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

	pinMode(RESET_PIN, INPUT_PULLUP);
	gpio_install_isr_service(0);
	gpio_set_intr_type(RESET_PIN, GPIO_INTR_ANYEDGE);
	gpio_isr_handler_add(RESET_PIN, gpioInterruptHandler, (void*) RESET_PIN);

	xTaskCreatePinnedToCore(
		messageClientTask,		   /* Function to implement the task */
		"messageClientTask", /* Name of the task */
		4096,				   /* Stack size in words */
		NULL,				   /* Task input parameter */
		5,					   /* Priority of the task */
		&xMessageClientTask,				   /* Task handle. */
		0);					   /* Core where the task should run */

	xTaskCreatePinnedToCore(
		lightMessageReceiverTask,		   /* Function to implement the task */
		"lightMessageReceiverTask", /* Name of the task */
		4096,				   /* Stack size in words */
		NULL,				   /* Task input parameter */
		5,					   /* Priority of the task */
		&xLightMessageReceiverTask,				   /* Task handle. */
		0);					   /* Core where the task should run */
	
	xTaskCreatePinnedToCore(
		lightUpdaterTask,		   /* Function to implement the task */
		"lightUpdaterTask", /* Name of the task */
		4096,				   /* Stack size in words */
		NULL,				   /* Task input parameter */
		4,					   /* Priority of the task */
		&xLightHandlerTask,				   /* Task handle. */
		1);					   /* Core where the task should run */

	xTaskCreatePinnedToCore(
		printFreeHeapTask,		   /* Function to implement the task */
		"printFreeHeapTask", /* Name of the task */
		4096,				   /* Stack size in words */
		NULL,				   /* Task input parameter */
		4,					   /* Priority of the task */
		NULL,				   /* Task handle. */
		1);					   /* Core where the task should run */

	xTaskCreatePinnedToCore(
		gpioInterruptHandlerTask,		   /* Function to implement the task */
		"gpioInterruptHandlerTask", /* Name of the task */
		2048,				   /* Stack size in words */
		NULL,				   /* Task input parameter */
		4,					   /* Priority of the task */
		NULL,				   /* Task handle. */
		1);					   /* Core where the task should run */
	
	xTaskCreatePinnedToCore(
		waitForUpdateTask,		   /* Function to implement the task */
		"waitForUpdateTask", /* Name of the task */
		16384,				   /* Stack size in words */
		NULL,				   /* Task input parameter */
		4,					   /* Priority of the task */
		NULL,				   /* Task handle. */
		1);					   /* Core where the task should run */

	Serial.println("Boot setup ran.");
}
