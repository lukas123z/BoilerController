#include "RelayManager.h"

RelayManagerClass::RelayManagerClass(float & _temperature) : temperature(_temperature), isCooling(false), maxTemperature(55)
{
	pinMode(RELAY_PIN, OUTPUT);
	pinMode(DIODE_PIN, OUTPUT);
	digitalWrite(RELAY_PIN, HIGH);
	state = CS_OFF;
}

RelayManagerClass::~RelayManagerClass()
{
}

void RelayManagerClass::maintain()
{
	if (state != CS_MAINTAINING) return;
	Serial.println("I'm maintaining");
	if (temperature >= maxTemperature) isCooling = true;
	else if (isCooling == false) powerOn();
	if (isCooling == true && temperature > maxTemperature - 10) powerOff();
	if (isCooling == true && temperature <= maxTemperature - 10) isCooling == false;
}

void RelayManagerClass::powerOff()
{
	digitalWrite(RELAY_PIN, HIGH); digitalWrite(DIODE_PIN, LOW);
}

void RelayManagerClass::powerOn()
{
	digitalWrite(RELAY_PIN, LOW); digitalWrite(DIODE_PIN, HIGH);
}



void RelayManagerClass::setState(CONTROLLERSTATE _state)
{
	state = _state;
}

void RelayManagerClass::securityCheck()
{
	if (temperature == 85.0f) return; //sensor shows 85 deegres when he has error
	if (state != CS_MAINTAINING && temperature >= maxTemperature) state = CS_OFF;
	if (temperature >= MAX_SECURITY_TEMP) state = CS_OFF;
}

void RelayManagerClass::commit()
{
	switch (state)
	{
	case CS_MAINTAINING: maintain(); break;
	case CS_OFF: powerOff(); break;
	case CS_ON: powerOn(); break;
	}
}

void RelayManagerClass::setMaxTemperature(int _temperature)
{
	if (_temperature >= MAX_SECURITY_TEMP - 5) return;
	maxTemperature = _temperature;
}

int RelayManagerClass::getMaxTemperature() const
{
	return maxTemperature;
}

CONTROLLERSTATE RelayManagerClass::getState() const
{
	return state;
}
