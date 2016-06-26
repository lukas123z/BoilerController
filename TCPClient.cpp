#include "TCPClient.h"

TCPClientClass::TCPClientClass(float & _temperature, RelayManagerClass & _RelayManager) : temperature( _temperature),
																						relayManager(_RelayManager)
{
}

TCPClientClass::~TCPClientClass()
{
}
