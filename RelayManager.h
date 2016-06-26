#pragma once
#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

enum CONTROLLERSTATE
{
	CS_MAINTAINING, CS_ON, CS_OFF
};

class RelayManagerClass
{
protected:
	int maxTemperature;
	float& temperature;
	CONTROLLERSTATE	state;
	bool isCooling;
	void maintain();
public:
	void setState(CONTROLLERSTATE _state);
	void securityCheck();
	void commit();
	void setMaxTemperature(int _temperature);
	int getMaxTemperature() const;
	CONTROLLERSTATE getState() const;

	RelayManagerClass(float& _temperature);
	~RelayManagerClass();
};


