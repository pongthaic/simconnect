#ifndef __PCF8574_H
#define __PCF8574_H

#include "./device.h"
#include <PCF8574.h>

enum PinState
{
    PIN_KEPT_LOW,
    PIN_KEPT_HIGH,
    PIN_RISING,
    PIN_FALLING,
};

class PinExpansion : public Device
{
public:
    PinExpansion(int addr = 0x20);

    void setup();
    void loop();
    int getData(int pin);

    void (*onUpdated)(enum PinState pins[]) = NULL;

    PCF8574 pcf;
    int addr;

private:
    uint8_t last = 0;
};

#include "./pin_expansion.cpp"
#endif