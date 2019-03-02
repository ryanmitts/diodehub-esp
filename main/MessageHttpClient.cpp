#include <FS.h>
#include <SPIFFS.h>
#include "MessageHttpClient.h"

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

unsigned long lastHeartbeatRun;

extern const uint8_t ca_certificates_pem_start[] asm("_binary_ca_certificates_pem_start");
extern const uint8_t ca_certificates_pem_end[] asm("_binary_ca_certificates_pem_end");

esp_tls_cfg_t cfg;

MessageHttpClient::MessageHttpClient()
{
	cfg.cacert_pem_buf = ca_certificates_pem_start;
	cfg.cacert_pem_bytes = ca_certificates_pem_end - ca_certificates_pem_start;
	isUsingSSL = true;
}

MessageHttpClient::~MessageHttpClient()
{
	delete wifiClient;
	delete webSocketClient;
}

// Start the message client with the passed in credentials.
bool MessageHttpClient::start(char *hostname, char *port, char *clientId, char *clientSecret)
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

bool MessageHttpClient::startSocket(bool force = false)
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
	char path[] = "/socket/?EIO=3&transport=websocket";
	webSocketClient->path = path;
	webSocketClient->host = hostname;
	Serial.println("Started handshake.");
	if (webSocketClient->handshake(*wifiClient))
	{
		Serial.println("Handshake passed.");
		return true;
	}
	else
	{
		Serial.println("Handshake failed.");
		return false;
	}
}

// Stop this controller.
void MessageHttpClient::stop()
{
	wifiClient->stop();
	started = false;
}

void MessageHttpClient::checkAndPerformHeartbeat()
{
	unsigned long ellapsedHeartbeat = millis() - lastHeartbeatRun;
	bool res = startSocket();
	while (res == false)
	{
		res = startSocket();
	}
	if (ellapsedHeartbeat > HEARTBEAT_INTERVAL)
	{
		sendHeartbeat();
		lastHeartbeatRun = millis();
	}
}

bool MessageHttpClient::checkAndReceiveMessage(JsonDocument* jsonBuffer)
{
	bool res = startSocket();
	while (res == false)
	{
		res = startSocket();
	}
	if (wifiClient->available())
	{
		String rawMessage;
		webSocketClient->getData(rawMessage);
		if (!rawMessage.length())
		{
			return false;
		}
		Serial.println(rawMessage);
		if (!rawMessage.startsWith("42"))
		{
			Serial.println("Unknown message type.");
			return false;
		}
		rawMessage.remove(0, 2);
		DeserializationError err = deserializeJson(*jsonBuffer, rawMessage);
		if (err)
		{
			Serial.println("Could not parse message.");
			return false;
		}
		return true;
		// const char *eventName = json[0].as<char *>();
		// if (strcmp(eventName, LIGHTS_MESSAGE_EVENT) == 0)
		// {
		// 	if (json[1].is<JsonObject>())
		// 	{
		// 		return true;
		// 	}
		// 	else
		// 	{
		// 		Serial.println("Message is not an object.");
		// 		return false;
		// 	}
		// }
		// else
		// {
		// 	Serial.println("Unsupported event.");
		// 	return false;
		// }
	}
	return false;
}

void MessageHttpClient::sendHeartbeat()
{
	Serial.println("Send heartbeat.");
	int freeHeap = ESP.getFreeHeap();
	double uptime = millis();
	StaticJsonDocument<128> heartbeatMsg;
	heartbeatMsg["uptime"] = uptime;
	heartbeatMsg["freeHeap"] = freeHeap;
	heartbeatMsg["version"] = UpdateHandler::getCurrentVersion();
	heartbeatMsg["md5"] = UpdateHandler::getCurrentMd5();
	char serializedMessage[256];
	serializeJson(heartbeatMsg, serializedMessage);
	String msg = "42[\"heartbeat\", ";
	msg += String(serializedMessage) + "]";
	webSocketClient->sendData(msg.c_str(), WS_OPCODE_TEXT);
}
