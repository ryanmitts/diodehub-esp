#pragma once

#include <Arduino.h>
#include <WebSocketClient.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <time.h>
#include <base64.h>
#include <ArduinoJson.h> 
#include "Callback.h"
#include "UpdateHandler.h"

class MessageHttpClient {
public:
  MessageHttpClient();
	~MessageHttpClient();
	bool start(char*, char*, char*, char*);
	void stop();
	void looper();
	Signal<JsonObject&> onMessageReceivedSignal;
private:
	bool started = false;
	char* hostname;
	char* port;
	char* clientId;
	char* clientSecret;
	WebSocketClient *webSocketClient;
	WiFiClient *wifiClient;
	int isUsingSSL;
	bool startSocket(bool);
	void getMessage();
	void sendHeartbeat();
};
