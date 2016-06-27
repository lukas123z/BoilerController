#include "WiFiManager.h"

bool WiFiManagerClass::connect()
{
	WiFi.config(IPAddress(OWNIP), IPAddress(GATEWAY), IPAddress(SUBNET_MASK), IPAddress(DNS));
	WiFi.begin(SSID, PASSWORD);

	unsigned long timeout = millis();
	while (WiFi.status() != WL_CONNECTED) 
	{
		delay(500);
		if (millis() - timeout > 10000) return false;
	}
	return true;
}

bool WiFiManagerClass::checkConnection()
{
	if (WiFi.status() != WL_CONNECTED)
	{
		if (connect()) return true;
		else return false;
	}
	return true;
}
