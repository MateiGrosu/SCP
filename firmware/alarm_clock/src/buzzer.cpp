#include "buzzer.h"

#include <HardwareSerial.h>
#include <Arduino.h>

static constexpr uint8_t BUZZER_PIN{ 17 };

void Buzzer::setup()
{
    // Initialize the buzzer pin as output
    pinMode(BUZZER_PIN, OUTPUT);
    turn_buzzer_off();
}

void Buzzer::activate()
{
    turn_buzzer_on();
    this->m_is_active = true;
}

void Buzzer::deactivate()
{
    turn_buzzer_off();
    this->m_is_active = false;
}

void turn_buzzer_on()
{
    digitalWrite(BUZZER_PIN, HIGH);
    //Serial.println("Buzzer is turned on");
}

void turn_buzzer_off()
{
    digitalWrite(BUZZER_PIN, LOW);
    //Serial.println("Buzzer is turned off");
}


bool Buzzer::is_active() const
{
    return this->m_is_active;
}
