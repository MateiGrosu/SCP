#pragma once

#include "SpinTimer.h"

class FuncSpinTimerAction : public SpinTimerAction
{
private:
    std::function<void()> callback;

public:
    explicit FuncSpinTimerAction(std::function<void()> callback) : callback(std::move(callback)){};

    void timeExpired() override
    {
        callback();
    }
};
