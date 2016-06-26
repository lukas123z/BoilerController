#include "RelayManager.h"
#include <OneWire/OneWire.h>
#include <DallasTemperature/DallasTemperature.h>
#include "TCPClient.h"
#include "WiFiManager.h"
#include "Definitions.h"

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature thermometer(&oneWire);
float temperature;
WiFiManagerClass WifiManager;
RelayManagerClass RelayManager(temperature);
TCPClientClass TCPClient(temperature, RelayManager);
void setup()
{
	thermometer.begin();
	WifiManager.connect();
}

void loop()
{
	temperature = getTemperature();
	WifiManager.checkConnection();
  

	
	
	RelayManager.securityCheck();
	RelayManager.commit();
}

float getTemperature()
{
	thermometer.requestTemperaturesByIndex(0);
	return thermometer.getTempCByIndex(0);
}
