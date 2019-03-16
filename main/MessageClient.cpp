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
#include "MessageClient.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "esp_system.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"

#include "esp_tls.h"

static unsigned int HEARTBEAT_INTERVAL = 60000;
static const int CA_CERT_MAX_SIZE = 4096;
static const int MESSAGE_BUFFER_SIZE = 8192;
static const char PONG[] = "pong";
static const char READY_MESSAGE[] = "{\"action\":\"ready\"}";

unsigned long lastHeartbeatRun;

extern const uint8_t ca_certificates_pem_start[] asm("_binary_ca_certificates_pem_start");
extern const uint8_t ca_certificates_pem_end[] asm("_binary_ca_certificates_pem_end");

esp_tls_cfg_t cfg;

MessageClient::MessageClient()
{
	cfg.cacert_pem_buf = ca_certificates_pem_start;
	cfg.cacert_pem_bytes = ca_certificates_pem_end - ca_certificates_pem_start;
	isUsingSSL = true;
}

MessageClient::~MessageClient()
{
	delete wifiClient;
	delete webSocketClient;
}

// Start the message client with the passed in credentials.
bool MessageClient::start(char *hostname, char *port, char *clientId, char *clientSecret)
{
	Serial.println(String("Message client starting with hostname: ") + hostname);
	webSocketClient = new WebSocketClient();
	this->hostname = hostname;
	this->port = port;
	this->clientId = clientId;
	this->clientSecret = clientSecret;
	String auth = clientId;
	auth += ":";
	auth += clientSecret;
	webSocketClient->authorization = base64::encode(auth);
	if (isUsingSSL)
	{
		wifiClient = new WiFiClientSecure();
	}
	else
	{
		wifiClient = new WiFiClient();
	}
	Serial.println("Done message client start.");
	started = true;
	return started;
}

bool MessageClient::startSocket(bool force = false)
{
	if (!force && wifiClient->connected())
	{
		return true;
	}
	if (isUsingSSL)
	{
		WiFiClientSecure *secureClient = static_cast<WiFiClientSecure *>(wifiClient);
		secureClient->setCACert((const char *)ca_certificates_pem_start);
	}
	if (!wifiClient->connect(hostname, atoi(port)))
	{
		Serial.println("Could not connect wifi client to host.");
		return false;
	};
	char path[] = "/";
	webSocketClient->path = path;
	webSocketClient->host = hostname;
	Serial.println("Started handshake.");
	if (webSocketClient->handshake(*wifiClient))
	{
		Serial.println("Handshake passed.");
		if (!this->firstInitDone) {
			sendReady();
			this->firstInitDone = true;
		}
		
		return true;
	}
	else
	{
		Serial.println("Handshake failed.");
		return false;
	}
}

// Stop this controller.
void MessageClient::stop()
{
	wifiClient->stop();
	started = false;
}

void MessageClient::checkAndPerformHeartbeat()
{
	unsigned long ellapsedHeartbeat = millis() - lastHeartbeatRun;
	bool res = startSocket();
	while (res == false)
	{
		res = startSocket();
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
	if (ellapsedHeartbeat > HEARTBEAT_INTERVAL)
	{
		sendHeartbeat();
		lastHeartbeatRun = millis();
	}
}

void MessageClient::sendPong()
{
	webSocketClient->sendData(PONG, WS_OPCODE_PONG);
}

bool MessageClient::checkAndReceiveMessage(JsonDocument *jsonBuffer)
{
	bool res = startSocket();
	while (res == false)
	{
		res = startSocket();
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
	if (wifiClient->available())
	{
		String message;
		uint8_t opcode;
		webSocketClient->getData(message, &opcode);
		if (opcode == WS_OPCODE_TEXT)
		{
			Serial.println("Got text frame.");
			Serial.println(message);
			if (!message.length())
			{
				Serial.println("No data.");
				return false;
			}
			DeserializationError err = deserializeJson(*jsonBuffer, message);
			if (err)
			{
				Serial.println("Could not parse message.");
				return false;
			}
			return true;
		}
		else if (opcode == WS_OPCODE_PING)
		{
			sendPong();
		}
		else
		{
			Serial.println("Unsupported websocket opcode.");
		}
	}
	return false;
}

void MessageClient::sendHeartbeat()
{
	Serial.println("Send heartbeat.");
	int freeHeap = ESP.getFreeHeap();
	double uptime = millis();
	StaticJsonDocument<256> doc;
	JsonObject root = doc.to<JsonObject>();
	root["action"] = "health";
	JsonObject body = root.createNestedObject("data");
	body["uptime"] = uptime;
	body["freeHeap"] = freeHeap;
	body["version"] = UpdateHandler::getCurrentVersion();
	body["md5"] = UpdateHandler::getCurrentMd5();
	char serializedMessage[256];
	serializeJson(root, serializedMessage);
	webSocketClient->sendData(serializedMessage, WS_OPCODE_TEXT);
}

void MessageClient::sendReady()
{
	webSocketClient->sendData(READY_MESSAGE, WS_OPCODE_TEXT);
}
