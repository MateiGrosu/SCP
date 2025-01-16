#include "sprinkler.h"

#include <HardwareSerial.h>

static void activate_sprinkler()
{
    Serial.println("Sprinkler on");
}

static void deactivate_sprinkler()
{
    Serial.println("Sprinkler off");
}

Sprinkler::Sprinkler() = default;

Sprinkler::~Sprinkler() = default;

void Sprinkler::activate()
{
    activate_sprinkler();
}

void Sprinkler::deactivate()
{
    deactivate_sprinkler();
}
