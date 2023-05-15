#ifndef __PCF8574_H
#define __PCF8574_H

#include "./device.h"
#include <PCF8574.h>

enum PinState
{
    PIN_KEPT_LOW = 0x00,
    PIN_KEPT_HIGH = 0x01,
    PIN_RISING = 0x02,
    PIN_FALLING = 0x04,
};

typedef void (*PinUpdateListener)(enum PinState);

class PinExpansion : public Device
{
public:
    PinExpansion(int addr = 0x20);

    void setup();
    void loop();
    int getData(int pin);

    void (*onUpdated)(enum PinState pins[]) = NULL;
    void setInputListener(int pin, PinUpdateListener listener);

    PCF8574 pcf;
    int addr;

private:
    uint8_t last = 0;
    PinUpdateListener *listeners;
};

#include "./pin_expansion.cpp"
#endif