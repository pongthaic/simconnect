#ifndef __PCF8574_H
#define __PCF8574_H

#include "./device.h"
#include <PCF8574.h>

class PinExpansion : public Device
{
public:
    PinExpansion(int addr = 0x20);

    void setup();
    void loop();
    int getData(int pin);
    PCF8574 pcf;
    int addr;
};

#include "./pin_expansion.cpp"
#endif