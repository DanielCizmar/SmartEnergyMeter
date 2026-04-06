#include <Arduino.h>
#include "config.h"
#include "pzem_reader.h"
#include "wifi_manager.h"

MeterData meterData;

void setup() {
  Serial.begin(115200);
  delay(1000);

  connectWifi(WIFI_SSID, WIFI_PASSWORD);
  printWifiStatus();

  initPzem(Serial2, PZEM_RX_PIN, PZEM_TX_PIN);
}

void loop() {
  ensureWifi(WIFI_SSID, WIFI_PASSWORD);

  meterData = readPzemData();

  if (meterData.valid) {
      printMeterData(meterData);
  } else {
      Serial.println("PZEM read failed.");
  }

  delay(DATA_READ_INTERVAL);
}