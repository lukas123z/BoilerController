#include "Switch.h"

bool SwitchClass::wasClicked()
{
	if (digitalRead(SWITCH_PIN) == switchPinLastState) return false;
	else return true;
}

void SwitchClass::saveActualState()
{
	switchPinLastState = digitalRead(SWITCH_PIN);
}

SwitchClass::SwitchClass()
{
	pinMode(SWITCH_PIN, INPUT);
}

SwitchClass::~SwitchClass()
{
}
