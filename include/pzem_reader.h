#ifndef PZEM_READER_H
#define PZEM_READER_H

#include <Arduino.h>

struct MeterData {
    float voltage;
    float current;
    float power;
    float energy;
    float frequency;
    float pf;
    bool valid;
};

void initPzem(HardwareSerial& serialPort, int rxPin, int txPin);
MeterData readPzemData();
void printMeterData(const MeterData& data);

#endif