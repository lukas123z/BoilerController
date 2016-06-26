#include "RelayManager.h"

RelayManagerClass::RelayManagerClass(float & _temperature): temperature(_temperature), isCooling(false)
{
	pinMode(RELAY_BUS, OUTPUT);
}

RelayManagerClass::~RelayManagerClass()
{
}

void RelayManagerClass::maintain()
{
	if (state != CS_MAINTAINING) return;
	if (temperature >= maxTemperature) isCooling = true;
	else if (isCooling == false) digitalWrite(RELAY_BUS, LOW);
	if (isCooling == true && temperature > maxTemperature - 10) digitalWrite(RELAY_BUS, HIGH);
	if (isCooling == true && temperature <= maxTemperature - 10) isCooling == false;
}

void RelayManagerClass::setOff()
{
	state = CS_OFF;
}

void RelayManagerClass::setOn()
{
	state = CS_ON;
}

void RelayManagerClass::setMaintaining()
{
	state = CS_MAINTAINING;
}

void RelayManagerClass::securityCheck()
{
	if (temperature == 85.0f) return; //sensor shows 85 deegres when he has error
	if (state != CS_MAINTAINING && temperature >= maxTemperature) state = CS_OFF;
	if (temperature >= MAX_SECURITY_TEMP) state = CS_OFF;
}

void RelayManagerClass::commit()
{
	if (state == CS_MAINTAINING) maintain;
	else if (state == CS_ON) digitalWrite(RELAY_BUS, LOW);
	else if (state == CS_OFF) digitalWrite(RELAY_BUS, HIGH);
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
