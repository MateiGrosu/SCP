#include <Arduino.h>
#include <HelloWorld.h>
#include <WiFi.h>

void setup() {
    Serial.begin(115200);
    while (!Serial) {}
    Serial.println("Serial port is ready!");
    Serial.printf("Greeting of the day: %s", greeting());
}

void loop() {

}