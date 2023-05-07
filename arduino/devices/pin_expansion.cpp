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

#define PIN_DATA(d, p) 0x01 & (d >> p) != 0

void PinExpansion::loop()
{
    uint8_t data = this->pcf.read8();
    if (this->onUpdated != NULL && this->last != data)
    {
        enum PinState result[8];
        for (int bit = 0; bit < 8; bit++)
        {
            int oldval = PIN_DATA(this->last, bit);
            int newval = PIN_DATA(data, bit);
            if (oldval == 0 && newval == 1)
                result[bit] = PIN_RISING;
            else if (oldval == 1 && newval == 0)
                result[bit] = PIN_FALLING;
            else if (oldval == newval == 1)
                result[bit] = PIN_KEPT_HIGH;
            else if (oldval == newval == 0)
                result[bit] = PIN_KEPT_LOW;
        }

        this->onUpdated(result);
        this->last = data;

        Serial.printf("pins = %x\n", data);
    }
}

int PinExpansion::getData(int pin)
{
    return 0;
}
