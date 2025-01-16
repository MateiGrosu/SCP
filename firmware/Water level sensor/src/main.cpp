#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display settings (I2C interface)
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1  // Built-in reset pin (not needed for most setups)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);  // Use I2C

// Pin for the water level sensor
#define SENSOR_PIN 14

void setup() {
  Serial.begin(115200); // Start serial communication

  // Initialize the OLED display (using I2C)
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Default I2C address is 0x3C
    Serial.println(F("SSD1306 display not found"));
    while (1); // Halt the program if display is not found
  }
  display.display();  // Wait for the display to initialize
  delay(2000);  // Wait for 2 seconds

  display.clearDisplay(); // Clear the display
}

void loop() {
  // Read the resistance from the water level sensor
  int sensorValue = analogRead(SENSOR_PIN);

  // Display the sensor value on the OLED screen
  display.clearDisplay();  // Clear the display
  display.setTextSize(1);  // Set text size
  display.setTextColor(SSD1306_WHITE); // Set text color to white
  display.setCursor(0, 0); // Set cursor to the top-left corner

  // Display the water resistance value on the first line
  display.print("Water Resistance: ");
  display.setCursor(0, 10);  // Move cursor to the next line (y=10)
  display.println(sensorValue);


  // Determine the water level and display it
  String waterLevel;
  if (sensorValue < 1200) {
    waterLevel = "Empty";
  } else if (sensorValue < 2500) {
    waterLevel = "Low";   
  } else if (sensorValue < 2800) {
    waterLevel = "Medium";
  } else {
    waterLevel = "High";
  }

  // Move the cursor to the next line and display the water level status
  display.setCursor(0, 30);  // Move cursor to the next line (Y = 30)
  display.print("Water Level: ");
  display.println(waterLevel);

  display.display();  // Update the OLED screen

  delay(1000);  // Wait for 1 second before reading again
}
