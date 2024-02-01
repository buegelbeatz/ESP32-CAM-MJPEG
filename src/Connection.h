#ifndef CONNECTION_h
#define CONNECTION_h 1

#include "header.h"
#include <WiFi.h>
#include <string>


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
};

#endif
