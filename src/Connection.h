#ifndef CONNECTION_h
#define CONNECTION_h 1

#include "header.h"
#include <WiFi.h>
#include <string>

#define CONNECTION_GATEWAY    192.168.2.1
#define CONNECTION_SUBNET     255.255.255.0
#define CONNECTION_DNS1       192.168.2.1
#define CONNECTION_DNS2       8.8.8.8

class Connection {
public:
  Connection();
  virtual ~Connection();
  virtual void setup();
  int loop();

private:
  const char *ssid = STR(SSID); // type your WIFI information inside the quotes
  const char *password = STR(WIFI_PASSWORD); // WIFI password
  const char *hostname = STR(DEVICE_NAME);
  const String ip = STR(ESP_IP);
  const String gateway = STR(CONNECTION_GATEWAY);
  const String subnet = STR(CONNECTION_SUBNET);
  const String dns1 = STR(CONNECTION_DNS1);
  const String dns2 = STR(CONNECTION_DNS2);
};

#endif
