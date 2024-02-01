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
      IPAddress ip = WiFi.localIP();
      Serial.print("\nWiFi connected with IP ");
      Serial.println(ip);
    } else {
      Serial.println("Restart device...");
      delay(100);
      WiFi.disconnect();
      esp_restart();
    }
}
