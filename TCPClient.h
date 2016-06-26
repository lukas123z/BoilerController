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
	float& temperature;
	RelayManagerClass& relayManager;
	
	void connect();
	void sendTemperature();
	void sendState();
	void sendMaxTemperature();
public:
	void communicate();

	TCPClientClass(float& _temperature, RelayManagerClass& _RelayManager);
	~TCPClientClass();
};



