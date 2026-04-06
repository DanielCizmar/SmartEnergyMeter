#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>

void connectWifi(const char* ssid, const char* password);
bool isWifiConnected();
void ensureWifi(const char* ssid, const char* password);
void printWifiStatus();

#endif