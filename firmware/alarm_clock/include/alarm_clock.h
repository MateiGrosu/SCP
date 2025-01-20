#pragma once

#include "SpinTimer.h"
#include <functional>
#include <utility>
#include <chrono>
#include <memory>
#include "sprinkler.h"
#include "button.h"
#include "StopWatch.h"
#include "timer_helper.h"

#include "nonstd/optional.hpp"
#include "buzzer.h"

using namespace std;
using nonstd::optional;
using nonstd::nullopt;

using system_time_point = chrono::time_point<chrono::system_clock>;

class DisableAlarmStatEntry
{
public:
    explicit DisableAlarmStatEntry(unsigned long time)
        : time(time)
    {
    }

    unsigned long time;
};

// class AlarmClockStatistics
// {
// public:
//     Statistics<DisableAlarmStatEntry, 10> disable_alarm_stat_statistics{};
// };

class Alarm
{
public:
    explicit Alarm(const system_time_point alarm): alarm(alarm) {}

    ~Alarm()
    {
        delete spin_timer;
        delete stop_timer;
        delete sprinkler_timer;
    }

    system_time_point alarm;
    SpinTimer* spin_timer{nullptr};
    SpinTimer* stop_timer{nullptr};
    SpinTimer* sprinkler_timer{nullptr};
    StopWatch stop_watch{};
    bool went_off{false};;
};

constexpr unsigned long sec_to_ms(const unsigned long sec)
{
    return sec * 1000;
}

class AlarmConfig
{
public:
    // Defines how much time passes between each beep.
    // Alarm starts beeping when the alarm goes off.
    // Unit is in milliseconds.
    unsigned long beep_interval{ 333 };

    // Defines after what time the alarm is stopped again, when not pressing the button.
    // Unit is in milliseconds.
    unsigned long shutdown_alarm_after{ sec_to_ms(300) };

    // Defines the time when the water starts spraying, when not pressing the button fast enough.
    // Unit is in milliseconds.
    unsigned long spray_water_after{ sec_to_ms(5) };
};

class AlarmClock
{
public:
    AlarmConfig m_alarm_config{};

private:
    optional<Alarm> m_alarm{};
    Buzzer* m_buzzer;
    Sprinkler* m_sprinkler;
    Button* m_button;


public:
    explicit AlarmClock(Buzzer* buzzer, Sprinkler* sprinkler, Button* button);

    bool isAlarmSchedule() const;

    void schedule_alarm(system_time_point alarm);

    void cancelAlarm();

    void checkAlarm();
};

void print_chrono_time(system_time_point now);