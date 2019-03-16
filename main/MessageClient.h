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

#pragma once

#include <Arduino.h>
#include <WebSocketClient.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <time.h>
#include <base64.h>
#include <ArduinoJson.h> 
#include "UpdateHandler.h"

class MessageClient {
public:
  MessageClient();
	~MessageClient();
	bool start(char*, char*, char*, char*);
	void stop();
	void checkAndPerformHeartbeat();
	bool checkAndReceiveMessage(JsonDocument*);
private:
	bool started = false;
	bool firstInitDone = false;
	char* hostname;
	char* port;
	char* clientId;
	char* clientSecret;
	WebSocketClient *webSocketClient;
	WiFiClient *wifiClient;
	int isUsingSSL;
	bool startSocket(bool);
	void sendHeartbeat();
	void sendPong();
	void sendReady();
};
