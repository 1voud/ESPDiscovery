#ifndef _DISCOVERY_h
#define _DISCOVERY_h

#include "Arduino.h"
#include <WiFiUdp.h>

#define DEFAULT_DISCOVERY_STRING "!xESP8266"

class Discovery {
private:
  WiFiUDP *udp;
  int udpPort;
  const char* answer;
  const char* discoveryString;
public:
  Discovery(WiFiUDP& udp, const char* answer, int port=5000, const char* discoveryString=DEFAULT_DISCOVERY_STRING);
  void handle();
};

#endif

