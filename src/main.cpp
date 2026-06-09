#include <Arduino.h>
#include "config.h"
#include "pzem_reader.h"
#include "wifi_manager.h"
#include "influx_writer.h"

MeterData meterData;

void setup() {
  Serial.begin(115200);
  delay(1000);

  connectWifi(WIFI_SSID, WIFI_PASSWORD);
  printWifiStatus();

  initPzem(Serial2, PZEM_RX_PIN, PZEM_TX_PIN);
  initInflux();
}

void loop() {
  ensureWifi(WIFI_SSID, WIFI_PASSWORD);

  meterData = readPzemData();

  if (meterData.valid) {
      printMeterData(meterData);
      sendMeterDataToInflux(meterData);
  } else {
      Serial.println("PZEM read failed.");
  }

  delay(DATA_READ_INTERVAL);
}