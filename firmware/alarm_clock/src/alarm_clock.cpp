#include "alarm_clock.h"
#include <iomanip>
#include <Arduino.h>
#include <iostream>
#include "sprinkler.h"
#include "StopWatch.h"

AlarmClock::AlarmClock(Buzzer* buzzer, Sprinkler* sprinkler, Button* button) : m_buzzer(buzzer), m_sprinkler(sprinkler), m_button(button)
{
    button->set_on_pressed([this]
    {
        this->cancelAlarm();
    });
}

bool AlarmClock::isAlarmSchedule() const
{
    return this->m_alarm.has_value();
}

void AlarmClock::schedule_alarm(const system_time_point alarm)
{
    this->m_alarm = optional<Alarm>(alarm);
    Serial.print("Schedule alarm at ");
    print_chrono_time(alarm);
}

void AlarmClock::cancelAlarm()
{
    this->m_alarm.reset();
    this->m_buzzer->deactivate();
    this->m_sprinkler->deactivate();
    Serial.println("Alarm cancelled");
}

void AlarmClock::checkAlarm()
{
    if (!this->m_alarm.has_value())
    {
        return;
    }
    if (this->m_alarm->went_off)
    {
        return;
    }

    // check if we reached the alarm time
    if (chrono::system_clock::now() <= this->m_alarm->alarm)
    {
        this->m_alarm->went_off = true;
        Buzzer* buzzer = this->m_buzzer;

        Serial.println("Start beeping");
        this->m_alarm->spin_timer = new SpinTimer(this->m_alarm_config.beep_interval, new FuncSpinTimerAction([buzzer]
        {
            if (buzzer->is_active())
            {
                buzzer->deactivate();
            }
            else
            {
                buzzer->activate();
            }
        }), true, true);

        Serial.println("Stop timer started");
        this->m_alarm->stop_timer = new SpinTimer(this->m_alarm_config.shutdown_alarm_after, new FuncSpinTimerAction([this]
        {
            this->cancelAlarm();
        }), false, true);

        Serial.println("Sprinkler timer started");
        this->m_alarm->sprinkler_timer = new SpinTimer(this->m_alarm_config.spray_water_after, new FuncSpinTimerAction([this]
        {
            this->m_sprinkler->activate();
        }), false, true);

    }
}

void print_chrono_time(system_time_point now) {
    // Convert to time_t for formatting
    const std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // Convert to local time
    const std::tm* localTime = std::localtime(&currentTime);

    // Print the current time using <iomanip>
    std::cout << "Current time: "
              << std::put_time(localTime, "%Y-%m-%d %H:%M:%S") << std::endl;
}