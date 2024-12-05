#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Button settings
#define BUTTON_PIN 18

// Buzzer settings
#define BUZZER_PIN 17

void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);

  // Initialize the button pin as input with internal pull-up
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Initialize the buzzer pin as output
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW); // Default: buzzer is off (LOW)

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 display not found"));
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Initializing...");
  display.display();
  delay(2000);
}

void loop() {
  // Read the button state (LOW = button pressed, HIGH = button not pressed)
  bool isPressed = digitalRead(BUTTON_PIN) == LOW;  // Normally closed: LOW = pressed, HIGH = not pressed

  // If the button is pressed, beep the buzzer (ON for 0.5s, OFF for 0.5s)
  if (isPressed) {
    digitalWrite(BUZZER_PIN, HIGH);  // Turn buzzer on
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Button: Pressed");
    display.println("Buzzer: ON");
    display.display();

    delay(200);                      // Keep the buzzer on for half a second

    digitalWrite(BUZZER_PIN, LOW);   // Turn buzzer off
    delay(200);                      // Keep the buzzer off for half a second
  } else {
    // If the button is not pressed, ensure buzzer is off
    digitalWrite(BUZZER_PIN, LOW);
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Button: Not Pressed");
    display.println("Buzzer: OFF");
    display.display();

    delay(100); // Small delay to make the display update visible
  }
}
