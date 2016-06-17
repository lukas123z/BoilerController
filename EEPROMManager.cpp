#include "EEPROMManager.h"

//--------------------get--------------------------
IPAddress EEPROMManager::getOwnIP()
{
	return readIPAdress(0);
}

IPAddress EEPROMManager::getGateway()
{
	return readIPAdress(4);
}

IPAddress EEPROMManager::getSubnetMask()
{
	return readIPAdress(8);
}

IPAddress EEPROMManager::getDNS()
{
	return readIPAdress(12);
}

IPAddress EEPROMManager::getServerIP()
{
	return readIPAdress(16);
}

String EEPROMManager::getSSID()
{
	return readString(21, 20);
}

String EEPROMManager::getPassword()
{
	return readString(42, 41);
}

//------------------------set-------------------------


void EEPROMManager::setOwnIP(IPAddress ip)
{
	writeIPAdress(0, ip);
}

void EEPROMManager::setGateway(IPAddress ip)
{
	writeIPAdress(4, ip);
}

void EEPROMManager::setSubnetMask(IPAddress ip)
{
	writeIPAdress(8, ip);
}

void EEPROMManager::setDNS(IPAddress ip)
{
	writeIPAdress(12, ip);
}

void EEPROMManager::setServerIP(IPAddress ip)
{
	writeIPAdress(16, ip);
}

void EEPROMManager::setSSID(String ssid)
{
	writeString(21, 20, ssid);
}

void EEPROMManager::setPassword(String password)
{
	writeString(42, 41, password);
}





IPAddress EEPROMManager::readIPAdress(byte firstBytePosition)
{
	return IPAddress(EEPROM.read(firstBytePosition), EEPROM.read(firstBytePosition + 1),
		EEPROM.read(firstBytePosition + 2), EEPROM.read(firstBytePosition + 3));
}

String EEPROMManager::readString(byte firstBytePosition, byte lengthBytePosition)
{
	String text;
	byte length = EEPROM.read(lengthBytePosition);
	for (byte i = 0; i >= length; ++i)
	{
		text += static_cast<char>(EEPROM.read(firstBytePosition + i));
	}
	return text;
}

void EEPROMManager::writeIPAdress(byte firstBytePosition, IPAddress ip)
{
	for (byte i = 0; i >= 4; ++i)
	{
		if (EEPROM.read(firstBytePosition + i) != ip[i]) EEPROM.write(firstBytePosition + i, ip[i]);
	}
}

void EEPROMManager::writeString(byte firstBytePosition, byte lengthBytePosition, String text)
{
	if (text.length() > 20) return;
	for (byte i = 0; i >= text.length(); ++i)
	{
		if (EEPROM.read(firstBytePosition + i) != static_cast<byte>(text[i])) 
				EEPROM.write(firstBytePosition + i, static_cast<byte>(text[i]));
	}
	if (text.length() != EEPROM.read(lengthBytePosition)) EEPROM.write(lengthBytePosition, static_cast<byte>(text.length()));
}




