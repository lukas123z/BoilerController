#include "WiFiManager.h"

void WiFiManagerClass::connect()
{
	WiFi.config(IPAddress(OWNIP), IPAddress(GATEWAY), IPAddress(SUBNET_MASK), IPAddress(DNS));
	WiFi.begin(SSID, PASSWORD);

	while (WiFi.status() != WL_CONNECTED) 
	{
		delay(500);
	}
}

void WiFiManagerClass::checkConnection()
{
	if (WiFi.status() != WL_CONNECTED) connect();

}
