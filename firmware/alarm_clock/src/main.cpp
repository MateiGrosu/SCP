#include <Arduino.h>
#include <WiFi.h>
#include "water_dispenser.h"
#include "buzzer.h"
#include "alarm_clock.h"
#include "SpinTimer.h"
#include <chrono>
#include <button.h>
#include <CircularBuffer.hpp>

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

void waitForTimeConfigured();

void postSetup();

void wait_for_serial();

void connect_to_wifi();

void configure_current_time();

void setup() {
    wait_for_serial();
    connect_to_wifi();
    configure_current_time();
    postSetup();
}

// When this function is called, time has been synchronized
void postSetup() {
    timer_handler.schedule_alarm(system_clock::now() += chrono::duration<int>(10));
}

void loop() {
    button.loop();
    scheduleTimers();
    timer_handler.checkAlarm();
}

void waitForTimeConfigured()
{
    struct tm timeinfo;
    while (!getLocalTime(&timeinfo)) {
        Serial.println("Waiting for time to be configured...");
        delay(1000);
    }
    Serial.println("Time is configured!");
}


void wait_for_serial()
{
    Serial.begin(SERIAL_BAUD);
    // Wait for the serial port to become available, so we can see what is being printed
    while (!Serial) {}
    Serial.println("Serial port is ready!");
}

void connect_to_wifi()
{
    WiFi.setHostname("Smart Alarm Clock");
    WiFi.setAutoReconnect(true);
    WiFi.begin("EricPcHotspot", "V|77o436");

    Serial.println("Waiting for WiFi connection...");
    // The alarm clock needs to current time, which it will receive from the internet.
    // For that reason, it has to wait until it is connected to the internet.
    while (!WiFi.isConnected()) {}
    Serial.println("Connected to WiFi");

    // Receive the current time from an NTP SERVER

    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}

void configure_current_time()
{
    Serial.println("Pulling current time from NTP...");
    configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, "pool.ntp.org");
    waitForTimeConfigured();
    const auto now = system_clock::now();
    Serial.print("Current time is: ");
    print_chrono_time(now);
}