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
	void waitForResponse();
public:	
	void connect();
	void sendStartMessage();
	void sendTemperature(float temp);
	CONTROLLERSTATE requestState();
	int requestMaxTemperature();
	void disconnect();


	TCPClientClass();
	~TCPClientClass();
};



