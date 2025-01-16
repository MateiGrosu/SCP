#include "button.h"

static bool isButtonPressed()
{
    // TODO Implement the logic to check if the button is pressed
    return false;
}

void Button::set_on_pressed(std::function<void()> callback)
{
    this->callback = std::move(callback);
}

void Button::loop()
{
    if (isButtonPressed() && this->callback)
    {
        this->callback();
    }
}
