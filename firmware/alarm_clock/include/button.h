#pragma once

#include <functional>
#include <SpinTimer.h>
#include "PushEventButton.h"

static constexpr uint8_t BUTTON_PIN = 13; // GPIO pin for the button (change as needed)

class Button
{
private:
    std::function<void()> callback;
    PushEventButton pushEvent{BUTTON_PIN, PushEventButton::CAPTUREPUSH};

public:
    void set_on_pressed(std::function<void()> callback);

    void setup();

    void slow_loop();
};
