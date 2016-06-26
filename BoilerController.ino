#include "WiFiManager.h"

WiFiManagerClass WifiManager;
void setup()
{
	WifiManager.connect();
}

void loop()
{
	WifiManager.checkConnection();
  

}
