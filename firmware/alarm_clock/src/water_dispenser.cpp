#include "water_dispenser.h"

void WaterDispenser::start_dispensing()
{
    this->is_active = true;
}

void WaterDispenser::stop_dispensing()
{
    this->is_active = false;
}
