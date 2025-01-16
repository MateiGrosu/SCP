#pragma once

class WaterDispenser
{
private:
    bool is_active{false};

public:
    void start_dispensing();

    void stop_dispensing();
};