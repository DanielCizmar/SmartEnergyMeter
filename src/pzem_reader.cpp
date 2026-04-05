#include "pzem_reader.h"
#include <PZEM004Tv30.h>
#include <math.h>

static PZEM004Tv30* pzem = nullptr;

void initPzem(HardwareSerial& serialPort, int rxPin, int txPin) {
    if (pzem != nullptr) {
        delete pzem;
        pzem = nullptr;
    }

    pzem = new PZEM004Tv30(serialPort, rxPin, txPin);
}

MeterData readPzemData() {
    MeterData data{0, 0, 0, 0, 0, 0, false};

    if (pzem == nullptr) {
        Serial.println("PZEM is not initialized.");
        return data;
    }

    data.voltage   = pzem->voltage();
    data.current   = pzem->current();
    data.power     = pzem->power();
    data.energy    = pzem->energy();
    data.frequency = pzem->frequency();
    data.pf        = pzem->pf();

    bool voltageOk   = !isnan(data.voltage);
    bool currentOk   = !isnan(data.current);
    bool powerOk     = !isnan(data.power);
    bool energyOk    = !isnan(data.energy);
    bool frequencyOk = !isnan(data.frequency);
    bool pfOk        = !isnan(data.pf);

    data.valid = voltageOk && currentOk && powerOk && energyOk && frequencyOk && pfOk;

    if (!data.valid) {
        Serial.println("Failed to read valid data from PZEM.");
    }

    return data;
}

void printMeterData(const MeterData& data) {
    if (!data.valid) {
        Serial.println("Invalid meter data.");
        return;
    }

    Serial.println("------ PZEM ------");
    Serial.print("Voltage: ");
    Serial.print(data.voltage);
    Serial.println(" V");

    Serial.print("Current: ");
    Serial.print(data.current);
    Serial.println(" A");

    Serial.print("Power: ");
    Serial.print(data.power);
    Serial.println(" W");

    Serial.print("Energy: ");
    Serial.print(data.energy);
    Serial.println(" kWh");

    Serial.print("Frequency: ");
    Serial.print(data.frequency);
    Serial.println(" Hz");

    Serial.print("PF: ");
    Serial.println(data.pf);

    Serial.println();
}