#include "influx_writer.h"
#include "config.h"

#include <WiFi.h>
#include <InfluxDbClient.h>

static const char* INFLUXDB_BUCKET = "EnergyConsuption";

static const char* MEASUREMENT_NAME = "pzem_data";

InfluxDBClient influxClient(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN);

Point meterPoint(MEASUREMENT_NAME);

void initInflux() {
    timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");
    
    meterPoint.addTag("device", "esp32");
    meterPoint.addTag("sensor", "pzem004t");

    Serial.println("Initializing InfluxDB...");

    if (influxClient.validateConnection()) {
        Serial.print("InfluxDB connected: ");
        Serial.println(influxClient.getServerUrl());
    } else {
        Serial.print("InfluxDB connection failed: ");
        Serial.println(influxClient.getLastErrorMessage());
    }
}

bool sendMeterDataToInflux(const MeterData& data) {
    if (!data.valid) {
        Serial.println("InfluxDB write skipped: invalid meter data.");
        return false;
    }

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("InfluxDB write skipped: WiFi not connected.");
        return false;
    }

    meterPoint.clearFields();

    meterPoint.addField("voltage", data.voltage);
    meterPoint.addField("current", data.current);
    meterPoint.addField("power", data.power);
    meterPoint.addField("energy", data.energy);
    meterPoint.addField("frequency", data.frequency);
    meterPoint.addField("pf", data.pf);

    // Voliteľne si vieš pozrieť line protocol
    Serial.print("Writing to InfluxDB: ");
    Serial.println(influxClient.pointToLineProtocol(meterPoint));

    if (influxClient.writePoint(meterPoint)) {
        Serial.println("InfluxDB write success.");
        return true;
    } else {
        Serial.print("InfluxDB write failed: ");
        Serial.println(influxClient.getLastErrorMessage());
        return false;
    }
}