#include <Arduino.h>
#include <WiFi.h>
#include "water_dispenser.h"
#include "buzzer.h"
#include "alarm_clock.h"
#include "SpinTimer.h"
#include <chrono>
#include <button.h>
#include <CircularBuffer.hpp>
#include "display_time.h"
#include "water_level.h"
#include "temperature.h"
#include "lorawan.h"

#include <iostream>
#include <ArduinoLog.h>
#include <sprinkler.h>

using namespace std::chrono;

constexpr unsigned long SERIAL_BAUD = 115200;
constexpr long GMT_OFFSET_SEC = 3600;
constexpr int DAYLIGHT_OFFSET_SEC = 3600;

Button button{};
WaterDispenser water_dispenser{};
Buzzer buzzer{};
Sprinkler sprinkler{};
AlarmClock timer_handler{ &buzzer, &sprinkler, &button };
TimeDisplay time_display{};
WaterLevelSensor water_level_sensor{};
Temperature temperature{};
LoRaWAN lorawan{};

void waitForTimeConfigured();
void postSetup();
void slow_loop();
void wait_for_serial();
void connect_to_wifi();
void configure_current_time();

void setup() {
    wait_for_serial();
    postSetup();
    // connect_to_wifi();
    // configure_current_time();
}

// When this function is called, time has been synchronized
void postSetup() {
    Serial.println("Enter post setup");

    button.setup();
    buzzer.setup();
    sprinkler.setup();
    time_display.setup();
    water_level_sensor.setup();

    if (!temperature.setup()) { // Initialize Temperature sensor
        Serial.println("Error: Temperature sensor failed to initialize!");
    }

    lorawan.initialize(); // Initialize LoRaWAN module

    timer_handler.schedule_alarm(system_clock::now() + chrono::duration<int>(10));

    new SpinTimer(10, new FuncSpinTimerAction([]
    {
        slow_loop();
    }), true , true);
}

void slow_loop() {
    button.slow_loop();

    float temp, humidity, pressure;

    // Read sensor data before sending
    if (temperature.readSensorData(temp, humidity, pressure)) {
        Serial.printf("Sending Data - Temp: %.2f, Humidity: %.2f, Pressure: %.2f\n", temp, humidity, pressure);
        lorawan.sendMessage(temp, humidity, pressure); // Send via LoRaWAN
    } else {
        Serial.println("Error: Failed to read temperature sensor data!");
    }
}

void loop() {
    scheduleTimers();
    timer_handler.checkAlarm();

    lorawan.runLoop();  // Keep LoRaWAN event processing active
}

void waitForTimeConfigured() {
    struct tm timeinfo;
    while (!getLocalTime(&timeinfo)) {
        Serial.println("Waiting for time to be configured...");
        delay(1000);
    }
    Serial.println("Time is configured!");
}

void wait_for_serial() {
    Serial.begin(SERIAL_BAUD);
    while (!Serial) {}
    Serial.println("Serial port is ready!");
}

void connect_to_wifi() {
    WiFi.setHostname("Smart Alarm Clock");
    WiFi.setAutoReconnect(true);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.println("Waiting for WiFi connection...");
    while (!WiFi.isConnected()) {}
    Serial.println("Connected to WiFi");

    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void configure_current_time() {
    Serial.println("Pulling current time from NTP...");
    configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, "pool.ntp.org");
    waitForTimeConfigured();
    const auto now = system_clock::now();
    Serial.print("Current time is: ");
    print_chrono_time(now);
}
