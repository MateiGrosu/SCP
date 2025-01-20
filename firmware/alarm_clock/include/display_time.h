#pragma once

#include <Adafruit_ILI9341.h>

#define TFT_CS 15
#define TFT_DC 2
#define TFT_RST 4

class TimeDisplay
{
private:
    Adafruit_ILI9341 tft { TFT_CS, TFT_DC, TFT_RST };

public:
    void setup();

    void update_displayed_time();
};

