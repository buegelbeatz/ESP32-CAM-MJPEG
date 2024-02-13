#include "connection.h"

// https://github.com/tzapu/WiFiManager/blob/master/examples/NonBlocking/AutoConnectNonBlocking/AutoConnectNonBlocking.ino

Connection::Connection() {}

Connection::~Connection() {}

int Connection::loop() {
  if (WiFi.status() == WL_CONNECTED) {
    return 1;
  } else {
    return 0;
  }
}

void Connection::setup() {
  Serial.println("Setup Connection...");
  IPAddress staticIp, gatewayIp, subnetMask, dnsServer1, dnsServer2;
  staticIp.fromString(this->ip);
  gatewayIp.fromString(this->gateway);
  subnetMask.fromString(this->subnet);
  dnsServer1.fromString(this->dns1);
  dnsServer2.fromString(this->dns2);
  if (WiFi.config(staticIp, gatewayIp, subnetMask, dnsServer1, dnsServer2) == false) {
    Serial.println("Configuration failed.");
  } else {
    WiFi.mode(WIFI_STA);
    WiFi.hostname(this->hostname);
    WiFi.begin(this->ssid, this->password);
    int counter = 0;
    while (WiFi.status() != WL_CONNECTED && counter < 100) {
      counter++;
      Serial.print(".");
      delay(100);
    }
    if (WiFi.status() == WL_CONNECTED) {
      Serial.print("http://");
      Serial.print(staticIp);
      Serial.println("/");
    }
  }
}
