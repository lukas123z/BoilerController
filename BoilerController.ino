#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include "RelayManager.h"
#include "TCPClient.h"
#include "WiFiManager.h"
#include "Definitions.h"
#include "Switch.h"


OneWire oneWire(ONE_WIRE_PIN);
DallasTemperature thermometer(&oneWire);
float temperature;
WiFiManagerClass WifiManager;
RelayManagerClass RelayManager(temperature);
TCPClientClass TCPClient;
SwitchClass Switch;
void setup()
{
	thermometer.begin();
	WifiManager.connect();
	Switch.saveActualState();
}

void loop()
{
	temperature = getTemperature();
	if (Switch.wasClicked()) RelayManager.switchOnOff();
	Switch.saveActualState();

	if (WifiManager.checkConnection() && TCPClient.connect())
	{ 
		TCPClient.sendMessage(temperature, RelayManager.getState());
		TCPClient.waitForResponse();
		TCPClient.translateResponeToData();
		RelayManager.setMaxTemperature(TCPClient.getMaxTemperatureFromServer());
		if (TCPClient.isStateChangedFromServer == true) RelayManager.setState(TCPClient.getStateFromServer());
		TCPClient.disconnect();
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
