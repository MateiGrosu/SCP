#include <display_time.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <chrono>

#define TFT_CS 15
#define TFT_DC 2
#define TFT_RST 4

void TimeDisplay::setup()
{
    tft.begin();
    tft.setRotation(1);
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(5);
    tft.setCursor(0, 0);
    tft.println("Hello World!");
}

void TimeDisplay::update_displayed_time()
{
    const auto now = std::chrono::system_clock::now();
    const time_t tt = std::chrono::system_clock::to_time_t(now);
    tm local_tm = *localtime(&tt);

    tft.fillScreen(ILI9341_BLACK);
    tft.fillRect(10, 50, 220, 100, ILI9341_BLACK);
    tft.setTextColor(ILI9341_GREEN);
    tft.setTextSize(3);
    tft.setCursor(10, 50);
    tft.printf("%02d:%02d:%02d", local_tm.tm_hour, local_tm.tm_min, local_tm.tm_sec);
    tft.setTextSize(2);
    tft.setCursor(10, 90);
    tft.setTextColor(ILI9341_YELLOW);
    tft.printf("%02d/%02d/%04d", local_tm.tm_mday, local_tm.tm_mon + 1, local_tm.tm_year + 1900);
}
