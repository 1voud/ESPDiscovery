// Java and Python Discovery samples can be found in the README.md
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include "ESPDiscovery.h"

char ssid[]     = "yourSSID";
char password[] = "yourPASSWORD";

WiFiUDP dsUDP;
Discovery discovery(dsUDP, "HereIam");

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting ...");
    delay(500);
    }
  Serial.println("Connected");  
}

void loop() {
  discovery.handle();
}