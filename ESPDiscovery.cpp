#include "ESPDiscovery.h"

Discovery::Discovery(WiFiUDP&wifiUDP, const char* answer, int port, const char* discoveryString) {
    this->udp = &wifiUDP;
    this->udpPort = port;
    this->answer = answer;
    this->discoveryString = discoveryString;
    this->udp->begin(udpPort);
}

void Discovery::handle() {
  int pktSize = this->udp->parsePacket();
  if (pktSize) {
    char pktBuf[pktSize+1];
    pktBuf[pktSize] = 0;
    this->udp->read(pktBuf, pktSize);
    if(strcmp(pktBuf, this->discoveryString) == 0) {
      this->udp->beginPacket(this->udp->remoteIP(), this->udp->remotePort());
      this->udp->write(this->answer);
      this->udp->endPacket();
    }
  }
}