#include <Arduino.h>
#include <PZEM004Tv30.h>

// ESP32 Serial2: RX = GPIO16, TX = GPIO17
PZEM004Tv30 pzem(Serial2, 16, 17);

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("PZEM test starting...");
  
  // Ak by si chcel vynulovať energiu:
  // pzem.resetEnergy();
}

void loop() {
  float voltage = pzem.voltage();
  float current = pzem.current();
  float power = pzem.power();
  float energy = pzem.energy();
  float frequency = pzem.frequency();
  float pf = pzem.pf();

  Serial.println("------ PZEM ------");

  if (!isnan(voltage)) {
    Serial.print("Voltage: ");
    Serial.print(voltage);
    Serial.println(" V");
  } else {
    Serial.println("Voltage: error");
  }

  if (!isnan(current)) {
    Serial.print("Current: ");
    Serial.print(current);
    Serial.println(" A");
  } else {
    Serial.println("Current: error");
  }

  if (!isnan(power)) {
    Serial.print("Power: ");
    Serial.print(power);
    Serial.println(" W");
  } else {
    Serial.println("Power: error");
  }

  if (!isnan(energy)) {
    Serial.print("Energy: ");
    Serial.print(energy, 3);
    Serial.println(" kWh");
  } else {
    Serial.println("Energy: error");
  }

  if (!isnan(frequency)) {
    Serial.print("Frequency: ");
    Serial.print(frequency, 1);
    Serial.println(" Hz");
  } else {
    Serial.println("Frequency: error");
  }

  if (!isnan(pf)) {
    Serial.print("PF: ");
    Serial.println(pf, 2);
  } else {
    Serial.println("PF: error");
  }

  Serial.println();
  delay(2000);
}