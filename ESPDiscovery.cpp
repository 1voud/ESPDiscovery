#include "ESPDiscovery.h"

Discovery::Discovery(char*answer, int port, char* discoveryString) {
    this->udpPort=port;
    this->answer=answer;
    this->discoveryString=discoveryString;
    discoveryUDP.begin(udpPort);
}

void Discovery::handle() {
  int pktSize = discoveryUDP.parsePacket();
  if (pktSize) {
    char pktBuf[pktSize+1];
    pktBuf[pktSize] = 0;
    discoveryUDP.read(pktBuf, pktSize);
    if(strcmp(pktBuf, discoveryString) == 0) {
      discoveryUDP.beginPacket(discoveryUDP.remoteIP(), discoveryUDP.remotePort());
      discoveryUDP.write(this->answer);
      discoveryUDP.endPacket();
    }
  }
}