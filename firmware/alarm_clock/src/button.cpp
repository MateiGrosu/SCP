#include "button.h"

#include <SpinTimer.h>
#include <Arduino.h>
#include "timer_helper.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BUTTONSUITEDEBUG
// OLED display settings
#define SCREEN_WIDTH 128 // OLED display width in pixels
#define SCREEN_HEIGHT 64 // OLED display height in pixels
#define OLED_RESET    -1 // Reset pin (not used, set to -1 for ESP32)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void Button::setup()
{
    pinMode(BUTTON_PIN, INPUT_PULLUP);

    // Initialize OLED display (using I2C)
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // 0x3C is the common I2C address for SSD1306 OLEDs
        Serial.println(F("SSD1306 display not found"));
        while (1);  // Halt the program if display is not found
    }

    display.clearDisplay();  // Clear the display
    display.setTextSize(1);  // Set text size to 1 (small)
    display.setTextColor(SSD1306_WHITE);  // Set text color to white
    display.setCursor(0, 0);  // Set cursor to the top-left corner
    display.println("Button: Not Pressed");
    display.display();  // Update the screen
}

void Button::set_on_pressed(std::function<void()> callback)
{
    this->callback = std::move(callback);
}

void Button::slow_loop()
{
    // Display logic
    display.clearDisplay();
    display.setCursor(0, 0);
    if (this->pushEvent.pushed()) {
        this->callback();
        display.println("Button: Pressed");
    } else {
        display.println("Button: Not Pressed");
    }

    display.display();
}
