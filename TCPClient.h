#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <ESP8266WiFi\src\WiFiClient.h>
#include "RelayManager.h"

class TCPClientClass
{
protected:
	WiFiClient client;
	CONTROLLERSTATE stateFromServer;
	int maxTemperatureFromServer;
	String controllerstateToString(CONTROLLERSTATE state);
public:	
	bool connect();
	void sendMessage(float temperatre, CONTROLLERSTATE state);
	bool waitForResponse();
	void translateResponeToData();
	bool isStateChanged;
	int getMaxTemperatureFromServer() const;
	CONTROLLERSTATE getStateFromServer();
	void disconnect();


	TCPClientClass();
	~TCPClientClass();
};



