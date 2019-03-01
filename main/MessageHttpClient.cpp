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
static const char LIGHTS_MESSAGE_EVENT[] = "lights";

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
	if (isUsingSSL) {
		wifiClient = new WiFiClientSecure();
	} else {
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

// Loop and check if we should poll for a new message.
void MessageHttpClient::looper()
{
	unsigned long ellapsedHeartbeat = millis() - lastHeartbeatRun;
	bool res = startSocket();
	while (res == false)
	{
		res = startSocket();
		delay(100);
	}
	if (ellapsedHeartbeat > HEARTBEAT_INTERVAL)
	{
		sendHeartbeat();
		lastHeartbeatRun = millis();
	}

	if (wifiClient->available())
	{
		getMessage();
	}
	delay(100);
}

// Get one message from the server.
void MessageHttpClient::getMessage()
{
	// Serial.println("Get message.");
	String rawMessage;
	webSocketClient->getData(rawMessage);
	if (!rawMessage.length())
	{
		return;
	}
	Serial.println(rawMessage);
	if (!rawMessage.startsWith("42"))
	{
		Serial.println("Unknown message type.");
		return;
	}
	rawMessage.remove(0, 2);
	DynamicJsonBuffer jsonBuffer(MESSAGE_BUFFER_SIZE);
	JsonArray &json = jsonBuffer.parseArray(rawMessage);
	if (!json.success())
	{
		Serial.println("Could not parse message.");
		return;
	}

	const char *eventName = json[0].as<char *>();
	if (strcmp(eventName, LIGHTS_MESSAGE_EVENT) == 0)
	{
		if (json[1].is<JsonObject>())
		{
			Serial.println("Firing to the lights delegator");
			onMessageReceivedSignal.fire(json[1].as<JsonObject>());
		}
		else
		{
			Serial.println("Message is not an object.");
		}
	}
	else
	{
		Serial.println("Unsupported event.");
		return;
	}
}

void MessageHttpClient::sendHeartbeat()
{
	Serial.println("Send heartbeat.");
	int freeHeap = ESP.getFreeHeap();
	double uptime = millis();
	StaticJsonBuffer<128> jb;
	JsonObject &heartbeatMsg = jb.createObject();
	heartbeatMsg["uptime"] = uptime;
	heartbeatMsg["freeHeap"] = freeHeap;
	heartbeatMsg["version"] = UpdateHandler::getCurrentVersion();
	heartbeatMsg["md5"] = UpdateHandler::getCurrentMd5();
	char serializedMessage[256];
	heartbeatMsg.printTo(serializedMessage);
	String msg = "42[\"heartbeat\", ";
	msg += String(serializedMessage) + "]";
	webSocketClient->sendData(msg.c_str(), WS_OPCODE_TEXT);
}
