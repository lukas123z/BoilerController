#pragma once
#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <ESP8266WiFi\src\ESP8266WiFi.h>
#include "Definitions.h"


class WiFiManagerClass
{
public:
	void connect();
	void checkConnection();

};



