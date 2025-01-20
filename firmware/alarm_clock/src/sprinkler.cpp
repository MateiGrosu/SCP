#include "sprinkler.h"

#include <HardwareSerial.h>
#include <Arduino.h>

static constexpr uint8_t SPRINKLER_PIN = 12;

static void activate_sprinkler()
{
    digitalWrite(SPRINKLER_PIN, HIGH);
    Serial.println("Sprinkler on");
}

static void deactivate_sprinkler()
{
    digitalWrite(SPRINKLER_PIN, LOW);
    Serial.println("Sprinkler off");
}

Sprinkler::Sprinkler() = default;

Sprinkler::~Sprinkler() = default;

void Sprinkler::setup()
{
    pinMode(SPRINKLER_PIN, OUTPUT);
}

void Sprinkler::activate()
{
    activate_sprinkler();
}

void Sprinkler::deactivate()
{
    deactivate_sprinkler();
}
