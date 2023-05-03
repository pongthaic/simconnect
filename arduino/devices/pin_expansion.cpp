#include "pin_expansion.h"

#include <PCF8574.h>

PinExpansion::PinExpansion(int _addr) : pcf(_addr)
{
    this->addr = _addr;
}

void PinExpansion::setup()
{
    this->pcf.begin();
}

void PinExpansion::loop()
{
}

int PinExpansion::getData(int pin)
{
    return 0;
}
