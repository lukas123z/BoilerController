#pragma once
#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Definitions.h"

class SwitchClass
{
 protected:
	 byte switchPinLastState;
 public:
	 bool wasClicked();
	 void saveActualState();

	 SwitchClass();
	 ~SwitchClass();
};
