#include "WiFiManager.h"

void WiFiManagerClass::connect()
{
	WiFi.config(IPAddress(OWNIP), IPAddress(GATEWAY), IPAddress(SUBNET_MASK), IPAddress(DNS));
	WiFi.begin(SSID, PASSWORD);

	unsigned long timeout = millis();
	while (WiFi.status() != WL_CONNECTED) 
	{
		delay(500);
		if (millis() - timeout > 10000) throw String("wifi connection error");
	}
}

void WiFiManagerClass::checkConnection()
{
	if (WiFi.status() != WL_CONNECTED) connect();

}
