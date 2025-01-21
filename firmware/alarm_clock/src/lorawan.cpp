// //
// // Created by Matei Grosu on 21.01.2025.
// //
//
// #include "lorawan.h"
// #include <Arduino.h> // Required for Serial, delay()
// #include <temperature.h>
//
// bool LoraWAN::pumpState = false;
// static osjob_t sendjob;
//
// const unsigned TX_INTERVAL = 10;
//
// const lmic_pinmap lmic_pins = {
//     .nss = 18,
//     .rxtx = LMIC_UNUSED_PIN,
//     .rst = 23,
//     .dio = {26, 33, 32},
// };
//
// // TTN Credentials (Replace with your actual values)
// static const u1_t APPEUI[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
// static const u1_t DEVEUI[8] = {0xD6, 0xD9, 0x06, 0xD0, 0x7E, 0xD5, 0xB3, 0x70};
// static const u1_t APPKEY[16] = {0xCD, 0xE8, 0xB4, 0x6D, 0xDE, 0x9B, 0xBB, 0xCD, 0xDA, 0x88, 0x11, 0x47, 0xCE, 0x90, 0xAA, 0x61};
//
// // Use standard memcpy instead of memcpy_P
// void os_getArtEui(u1_t *buf) { memcpy(buf, APPEUI, 8); }
// void os_getDevEui(u1_t *buf) { memcpy(buf, DEVEUI, 8); }
// void os_getDevKey(u1_t *buf) { memcpy(buf, APPKEY, 16); }
//
// LoraWAN::LoraWAN() {}
//
// void LoraWAN::setup() {
//     Serial.begin(115200);
//     delay(2000);
//     Serial.println("Initializing LoraWAN...");
//
//     SPI.begin(5, 19, 27, lmic_pins.nss);
//
//
//     // This initializes the LMIC stack
//     os_init_ex((const void *)&lmic_pins);
//
//     // It clears previous LoRaWAN sessions and prepares the module to start fresh.
//     LMIC_reset();
//
//
//     // responsible for transmitting LoRaWAN uplink messages.
//     sendMessage(&sendjob);
// }
//
// void LoraWAN::sendMessage( osjob_t *j) {
//
//
//     float temper, humidity, pressure;
//     // temperature.readSensorData(temper, humidity, pressure);
//
//     // 7 byte buffer to store the payload (values 0-255)
//     uint8_t payload[7];
//
//     // Convert float values to integer values
//     int16_t temp = (int16_t)(temper * 100);
//     uint16_t hum = (uint16_t)(humidity * 100);
//     uint32_t pres = (uint32_t)(pressure * 100);
//
//     // break into high and low (+medium) bytes and store in payload
//     payload[0] = (temp >> 8) & 0xFF;
//     payload[1] = temp & 0xFF;
//     payload[2] = (hum >> 8) & 0xFF;
//     payload[3] = hum & 0xFF;
//     payload[4] = (pres >> 16) & 0xFF;
//     payload[5] = (pres >> 8) & 0xFF;
//     payload[6] = pres & 0xFF;
//
//     // Send the payload. Check first if the module is busy.
//     if (LMIC.opmode & OP_TXRXPEND) {
//         Serial.println("OP_TXRXPEND, not sending");
//     } else {
//         LMIC_setTxData2(1, payload, sizeof(payload), 0);
//         Serial.println("Packet queued");
//     }
//
//     // Schedule the next transmission afetr TX_INTERVAL seconds, and converts the seconds
//     // into the LMIC system time and the do_send will be called again at the scheduled time
//     os_setTimedCallback(&sendjob, os_getTime() + sec2osticks(TX_INTERVAL), do_send);
// }
//
// void LoraWAN::onEvent(ev_t ev) {
//     Serial.print("Event: ");
//     Serial.println(ev);
//
//     switch (ev) {
//         case EV_JOINING:
//             Serial.println("Joining...");
//             break;
//         case EV_JOINED:
//             LMIC_setLinkCheckMode(0);
//             Serial.println("Joined LoRaWAN Network!");
//             break;
//         case EV_TXCOMPLETE:
//             Serial.println("Transmission complete.");
//
//             if (LMIC.dataLen > 0) {
//                 Serial.print("Downlink Received: ");
//                 for (int i = 0; i < LMIC.dataLen; i++) {
//                     Serial.print(LMIC.frame[i], HEX);
//                     Serial.print(" ");
//                 }
//                 Serial.println();
//
//                 if (LMIC.frame[0] == 0x01) {
//                     pumpState = true;
//                     Serial.println("Pump Turned ON!");
//                 } else if (LMIC.frame[0] == 0x00) {
//                     pumpState = false;
//                     Serial.println("Pump Turned OFF!");
//                 } else {
//                     Serial.println("Unknown Downlink Command");
//                 }
//             }
//             break;
//         default:
//             Serial.print("Unknown event: ");
//             Serial.println(ev);
//             break;
//     }
// }
//
// void LoraWAN::runLoop() {
//     // os_runloop_once();
// }
