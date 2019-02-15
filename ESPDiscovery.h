#ifndef _DISCOVERY_h
#define _DISCOVERY_h

#include "Arduino.h"
#include <WiFiUdp.h>

class Discovery {
private:
  int udpPort;
  WiFiUDP discoveryUDP;
  char* answer;
  char* discoveryString;
public:
  Discovery(char*answer, int port=5000, char* discoveryString="!xESP8266");
  void handle();
};

#endif

