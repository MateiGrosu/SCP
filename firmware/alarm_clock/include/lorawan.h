//
// Created by Matei Grosu on 21.01.2025.
//

#ifndef LORAWAN_H
#define LORAWAN_H


#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>

class LoRaWAN {
public:
    LoRaWAN();
    ~LoRaWAN();

    void initialize();
    void sendMessage(float temperature, float humidity, float pressure);
    void runLoop();

private:
    static void onEvent(ev_t ev);
    static void do_send(osjob_t *j);

    static osjob_t sendjob;
    static bool pumpState;
};



#endif //LORAWAN_H
