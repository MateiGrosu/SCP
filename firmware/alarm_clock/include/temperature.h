//
// Created by Matei Grosu on 20.01.2025.
//

#ifndef TEMPERATURE_H
#define TEMPERATURE_H


#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

class Temperature {
public:
    Temperature();
    bool setup();  // Initialize the sensor
    bool readSensorData(float &temperature, float &humidity, float &pressure); // Reads values

private:
    Adafruit_BME280 bme;
    bool isInitialized = false;
};



#endif //TEMPERATURE_H
