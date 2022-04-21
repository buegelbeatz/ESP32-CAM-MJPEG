#include "connection.h"

// https://github.com/tzapu/WiFiManager/blob/master/examples/NonBlocking/AutoConnectNonBlocking/AutoConnectNonBlocking.ino

Connection::Connection() {}

Connection::~Connection() {}

int Connection::loop() {
  if (WiFi.status() == WL_CONNECTED || this->apStatus == 1) {
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
  if (WiFi.config(staticIp, gatewayIp, subnetMask, dnsServer1, dnsServer2) ==
      false) {
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
    } else {
      Serial.println("Switch to AP-Mode...");
      WiFi.persistent(false);
      WiFi.setAutoConnect(false);
      WiFi.disconnect(true);
      WiFi.mode(WIFI_AP);
      delay(1000);
      WiFi.softAP(this->hostname, this->password);
      Serial.print("http://");
      Serial.print(WiFi.softAPIP());
      Serial.println("/");
      this->apStatus = 1;
    }
  }
}
