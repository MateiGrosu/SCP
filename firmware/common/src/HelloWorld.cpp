#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// OLED display settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// BME280 sensor settings
Adafruit_BME280 bme;
#define SEALEVELPRESSURE_HPA (1013.25)

// LoRaWAN keys and configurations
static const u1_t PROGMEM APPEUI[8] = {APPEUI};
void os_getArtEui(u1_t *buf) { memcpy_P(buf, APPEUI, 8); }

static const u1_t PROGMEM DEVEUI[8] = {DEVEUI};
void os_getDevEui(u1_t *buf) { memcpy_P(buf, DEVEUI, 8); }

static const u1_t PROGMEM APPKEY[16] = {APPKEY};
void os_getDevKey(u1_t *buf) { memcpy_P(buf, APPKEY, 16); }

static osjob_t sendjob;

// Transmission interval in seconds
const unsigned TX_INTERVAL = 30;

// Pin mapping for LoRa module
const lmic_pinmap lmic_pins = {
    .nss = 18,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = 23,
    .dio = {26, 33, 32},
};

// Function prototypes
void displaySensorData(float temperature, float humidity, float pressure);
void do_send(osjob_t *j);

void setup() {
  Serial.begin(9600);
  Serial.println(F("Starting..."));

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  display.clearDisplay();
  display.display();

  // Initialize BME280 sensor
  if (!bme.begin(0x76)) {
    Serial.println(F("BME280 sensor not found! Check wiring."));
    while (1)
      ;
  }

  // Initialize LoRa
  SPI.begin(5, 19, 27, lmic_pins.nss);
  os_init_ex((const void *)&lmic_pins);
  LMIC_reset();

  // Start the first job
  do_send(&sendjob);
}

void loop() {
  os_runloop_once();
}

void do_send(osjob_t *j) {
  // Read data from BME280
  float temperature = bme.readTemperature();
  float humidity = bme.readHumidity();
  float pressure = bme.readPressure() / 100.0F; // Convert to hPa

  // Display sensor data on OLED
  displaySensorData(temperature, humidity, pressure);

  // Prepare data for LoRa transmission
  uint8_t payload[7];
  int16_t temp = (int16_t)(temperature * 100);
  uint16_t hum = (uint16_t)(humidity * 100);
  uint32_t pres = (uint32_t)(pressure * 100);

  payload[0] = (temp >> 8) & 0xFF;
  payload[1] = temp & 0xFF;
  payload[2] = (hum >> 8) & 0xFF;
  payload[3] = hum & 0xFF;
  payload[4] = (pres >> 16) & 0xFF;
  payload[5] = (pres >> 8) & 0xFF;
  payload[6] = pres & 0xFF;

  // Check if the LoRa module is busy
  if (LMIC.opmode & OP_TXRXPEND) {
    Serial.println(F("OP_TXRXPEND, not sending"));
  } else {
    // Send data
    LMIC_setTxData2(1, payload, sizeof(payload), 0);
    Serial.println(F("Packet queued"));
  }

  // Schedule the next transmission
  os_setTimedCallback(&sendjob, os_getTime() + sec2osticks(TX_INTERVAL), do_send);
}

void displaySensorData(float temperature, float humidity, float pressure) {
  display.clearDisplay();

  // Display temperature
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print(F("Temp: "));
  display.print(temperature, 2);
  display.println(F(" C"));

  // Display humidity
  display.setCursor(0, 16);
  display.print(F("Humidity: "));
  display.print(humidity, 2);
  display.println(F(" %"));

  // Display pressure
  display.setCursor(0, 32);
  display.print(F("Pressure: "));
  display.print(pressure, 2);
  display.println(F(" hPa"));

  display.display();
}