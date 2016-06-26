#include <OneWire/OneWire.h>
#include <DallasTemperature/DallasTemperature.h>
#include "RelayManager.h"
#include "TCPClient.h"
#include "WiFiManager.h"
#include "Definitions.h"

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature thermometer(&oneWire);
float temperature;
WiFiManagerClass WifiManager;
RelayManagerClass RelayManager(temperature);
TCPClientClass TCPClient;
void setup()
{
	Serial.begin(115200);
	thermometer.begin();
	WifiManager.connect();
}

void loop()
{
	temperature = getTemperature();
	try 
	{
		WifiManager.checkConnection();
		TCPClient.connect();
		TCPClient.sendStartMessage();
		TCPClient.sendTemperature(temperature);
		RelayManager.setMaxTemperature(TCPClient.requestMaxTemperature());
		RelayManager.setState(TCPClient.requestState());
		TCPClient.disconnect();
	}
	catch (String e)
	{
		Serial.println(e);
	}
	RelayManager.securityCheck();
	RelayManager.commit();
	delay(5000);
}

float getTemperature()
{
	thermometer.requestTemperaturesByIndex(0);
	return thermometer.getTempCByIndex(0);
}
