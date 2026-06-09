#ifndef INFLUX_WRITER_H
#define INFLUX_WRITER_H

#include <Arduino.h>
#include "pzem_reader.h"

void initInflux();
bool sendMeterDataToInflux(const MeterData& data);

#endif