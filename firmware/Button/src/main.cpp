
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display settings
#define SCREEN_WIDTH 128 // OLED display width in pixels
#define SCREEN_HEIGHT 64 // OLED display height in pixels
#define OLED_RESET    -1 // Reset pin (not used, set to -1 for ESP32)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Button settings
#define BUTTON_PIN 18 // GPIO pin for the button (change as needed)
#define DEBOUNCE_DELAY 50 // Debounce time in milliseconds
#define HOLD_DELAY 2000 // Time to hold "Pressed" state after release in milliseconds

// State variables
bool buttonPressed = false;
unsigned long lastButtonPress = 0; 
unsigned long releaseTime = 0;

void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);

  // Initialize the button pin as input with internal pull-up
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Start serial monitor for debugging
  Serial.begin(115200);

  // Initialize OLED display (using I2C)
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // 0x3C is the common I2C address for SSD1306 OLEDs
    Serial.println(F("SSD1306 display not found"));
    while (1);  // Halt the program if display is not found
  }

  display.clearDisplay();  // Clear the display
  display.setTextSize(1);  // Set text size to 1 (small)
  display.setTextColor(SSD1306_WHITE);  // Set text color to white
  display.setCursor(0, 0);  // Set cursor to the top-left corner
  display.println("Hello, OLED!");  // Display a simple message
  display.display();  // Update the screen
  delay(2000);  // Wait for 2 seconds
}


void loop() {
  static bool wasPressed = false;

  // Read the button state (normally closed: LOW = not pressed, HIGH = pressed)
  bool isPressed = digitalRead(BUTTON_PIN) == HIGH;

  // Handle debouncing
  if (isPressed != wasPressed) {
    delay(DEBOUNCE_DELAY);
    wasPressed = isPressed;
    if (isPressed) {
      buttonPressed = true;
      lastButtonPress = millis();
    } else {
      releaseTime = millis(); // Record release time
    }
  }


  // Display logic
  display.clearDisplay();
  display.setCursor(0, 0);
  
  if (buttonPressed) {
    if (!isPressed && millis() - releaseTime >= HOLD_DELAY) {
      // After holding the "Pressed" state for 2 seconds, reset to "Not Pressed"
      buttonPressed = false;
    }
    display.println("Button: Pressed");
  } else {
    display.println("Button: Not Pressed");
  }

  display.display();
}