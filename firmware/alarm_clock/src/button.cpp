#include "button.h"

#include <SpinTimer.h>
#include <Arduino.h>
#include "timer_helper.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

void Button::setup()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void Button::set_on_pressed(std::function<void()> callback)
{
    this->callback = std::move(callback);
}

void Button::slow_loop()
{
    // Display logic
    if (this->pushEvent.pushed()) {
        this->callback();
    }
}
