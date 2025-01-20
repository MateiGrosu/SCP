#pragma once

static void turn_buzzer_on();

static void turn_buzzer_off();

class Buzzer
{
private:
    bool m_is_active{false};

public:
    void setup();

    void activate();

    void deactivate();

    bool is_active() const;
};

