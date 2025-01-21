//
// Created by Matei Grosu on 20.01.2025.
//

#include "temperature.h"
#include <Wire.h>
#include <Arduino.h>

Temperature::Temperature() {}

bool Temperature::setup() {
    isInitialized = bme.begin(0x76);  // Default I2C address for BME280
    if (!isInitialized) {
        Serial.println(" BME280 sensor not found!");
    } else {
        Serial.println(" BME280 sensor initialized.");
    }
    return isInitialized;
}

bool Temperature::readSensorData(float &temperature, float &humidity, float &pressure) {
    if (!isInitialized) {
        Serial.println(" BME280 sensor is not initialized!");
        return false;
    }

    temperature = bme.readTemperature();
    humidity = bme.readHumidity();
    pressure = bme.readPressure() / 100.0F; // Convert to hPa

    if (isnan(temperature) || isnan(humidity) || isnan(pressure)) {
        Serial.println(" Failed to read from BME280 sensor!");
        return false;
    }

    return true;
}