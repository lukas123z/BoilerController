#include "TCPClient.h"

bool TCPClientClass::waitForResponse()
{
	unsigned long timeout = millis();
	while (client.available() == 0)
	{
		if (millis() - timeout > 5000)
		{
			client.stop();
			Serial.println("server doesn't response");
			return false;
		}
		return true;
	}
}

void TCPClientClass::translateResponeToData()
{
	String parameter, value;
	while (client.available())
	{
		parameter = client.readStringUntil('=');
		value = client.readStringUntil('\r');
		Serial.println(parameter);
		Serial.println(value);

		if (parameter == "maxtemperature")
		{
			maxTemperatureFromServer = value.toInt();
		}
		else if (parameter = "changestate")
		{
			if (value == "NOT") { isStateChangedFromServer = false; break; }
			else isStateChangedFromServer = true;

			if (value == "ON") stateFromServer = CS_ON;
			if (value == "OFF") stateFromServer = CS_OFF;
			if (value == "MAINTAINING") stateFromServer = CS_MAINTAINING;
		}
	}
}

int TCPClientClass::getMaxTemperatureFromServer() const
{
	return maxTemperatureFromServer;
}

CONTROLLERSTATE TCPClientClass::getStateFromServer()
{
	isStateChangedFromServer = false;
	return stateFromServer;
}

String TCPClientClass::controllerstateToString(CONTROLLERSTATE state)
{
	if (state == CS_ON) return String("ON");
	if (state == CS_OFF) return String("OFF");
	if (state == CS_MAINTAINING) return String("MAINTAINING");
}

bool TCPClientClass::connect()
{
	return (client.connect(IPAddress(SERVER_IP), SERVER_PORT));
}

void TCPClientClass::sendMessage(float temperature, CONTROLLERSTATE state)
{
	String message;
	message += "name=BoilerController\r";
	message += "temperature" + String(temperature) + "\r";
	message += "state=" + controllerstateToString(state) + "\r";
	client.print(message);
}

void TCPClientClass::disconnect()
{
	client.flush();
	client.stop();
	Serial.println("Client disconnected");
}

TCPClientClass::TCPClientClass() : maxTemperatureFromServer(55), client()
{
}

TCPClientClass::~TCPClientClass()
{
}
