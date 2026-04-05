#include <Arduino.h>
#include "pzem_reader.h"

#define PZEM_RX_PIN 16
#define PZEM_TX_PIN 17
#define DATA_READ_INTERVAL 2000

MeterData meterData;

void setup() {
  Serial.begin(115200);
  delay(1000);

  initPzem(Serial2, PZEM_RX_PIN, PZEM_TX_PIN);
}

void loop() {
  meterData = readPzemData();

  if (meterData.valid) {
      printMeterData(meterData);
  } else {
      Serial.println("PZEM read failed.");
  }

  delay(DATA_READ_INTERVAL);
}