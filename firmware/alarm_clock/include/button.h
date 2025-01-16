#pragma once

#include <functional>

class Button
{
private:
    std::function<void()> callback;

public:
    void set_on_pressed(std::function<void()> callback);

    void loop();
};