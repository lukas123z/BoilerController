#include "TCPClient.h"

void TCPClientClass::waitForResponse()
{
	unsigned long timeout = millis();
	while (client.available() == 0)
	{
		if (millis() - timeout > 5000)
		{
			client.stop();
			throw String("Client timeout");
		}
	}
}

void TCPClientClass::connect()
{
	if (client.connect(IPAddress(SERVER_IP), SERVER_PORT) == false) throw String("connection to server error");
}

void TCPClientClass::sendStartMessage()
{
	client.print("name=BoilerController");

}

void TCPClientClass::sendTemperature(float temp)
{
	String message = "temperature=";
	message += temp;
	client.print(message);
}

CONTROLLERSTATE TCPClientClass::requestState()
{
	client.print("request=state");
	waitForResponse();
	String info = client.readStringUntil('=');
	String state = client.readString;
	client.flush();
	if (state == "CS_OFF") return CS_OFF;
	if (state == "CS_ON") return CS_ON;
	if (state == "CS_MAINTAINING") return CS_MAINTAINING;

}

int TCPClientClass::requestMaxTemperature()
{
	client.print("request=maxtemperature");
	waitForResponse();
	String info = client.readStringUntil('=');
	String maxTemp = client.readString;
	client.flush();
	return maxTemp.toInt;
}

void TCPClientClass::disconnect()
{
	client.flush();
	client.stop();
}

TCPClientClass::TCPClientClass()
{
}

TCPClientClass::~TCPClientClass()
{
}
