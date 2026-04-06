#include "wifi_manager.h"
#include <WiFi.h>

void connectWifi(const char* ssid, const char* password) {
    Serial.print("Connecting to WiFi: ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    int attempts = 0;
    const int maxAttempts = 5;

    while (WiFi.status() != WL_CONNECTED && attempts < maxAttempts) {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    Serial.println();

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("WiFi connected successfully.");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("Failed to connect to WiFi.");
    }
}

bool isWifiConnected() {
    return WiFi.status() == WL_CONNECTED;
}

void ensureWifi(const char* ssid, const char* password) {
    if (!isWifiConnected()) {
        Serial.println("WiFi connection lost. Reconnecting...");
        WiFi.disconnect();
        delay(500);
        connectWifi(ssid, password);
    }
}

void printWifiStatus() {
    if (isWifiConnected()) {
        Serial.println("WiFi status: CONNECTED");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        Serial.print("RSSI: ");
        Serial.print(WiFi.RSSI());
        Serial.println(" dBm");
    } else {
        Serial.println("WiFi status: DISCONNECTED");
    }
}