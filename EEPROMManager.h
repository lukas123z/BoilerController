//EEPROM doesn't work correctly on my ESP, so i don't know if EEPROMManager work or not



#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include <EEPROM/EEPROM.h>
#include <IPAddress.h>

class EEPROMManager
{
public:
	IPAddress getOwnIP();
	IPAddress getGateway();
	IPAddress getSubnetMask();
	IPAddress getDNS();
	IPAddress getServerIP();
	String getSSID();
	String getPassword();
	word getServerPort();
	void setOwnIP(IPAddress ip);
	void setGateway(IPAddress ip);
	void setSubnetMask(IPAddress ip);
	void setDNS(IPAddress ip);
	void setServerIP(IPAddress ip);
	void setSSID(String ssid);
	void setPassword(String password);
	void setServerPort(word port);
private:
	IPAddress readIPAddress(byte firstBytePosition);
	String readString(byte firstBytePosition, byte lengthBytePosition);
	void writeIPAddress(byte firstBytePosition, IPAddress ip);
	void writeString(byte firstBytePosition, byte lengthBytePosition, String text);
};

/*
Which bytes keeps which infornations
0-3 own ip
4-7 gateway
8-11 subnet mask
12-15 dns
16-19 server ip
20 ssid length(max 20)
21-40 ssid
41 password length(max 20)
42-61 password
62-63 server port
*/