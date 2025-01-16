#include "buzzer.h"

#include <HardwareSerial.h>

#include "alarm_clock.h"

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
    // TODO Add here the hardware code to turn the buzzer on
    Serial.println("Buzzer is turned on");
}

void turn_buzzer_off()
{
    // TODO Add here the hardware code to turn the buzzer off
    Serial.println("Buzzer is turned off");
}


bool Buzzer::is_active() const
{
    return this->m_is_active;
}
