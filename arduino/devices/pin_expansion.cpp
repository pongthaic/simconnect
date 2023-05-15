#include "pin_expansion.h"

#include <PCF8574.h>
#include <malloc.h>

#define PCF_UPDATE_RATE 100

PinExpansion::PinExpansion(int _addr) : pcf(_addr)
{
    this->addr = _addr;
    this->listeners = (PinUpdateListener *)malloc(sizeof(PinUpdateListener) * 8);
    for (int i = 0; i < 8; i++)
        this->listeners[i] = NULL;
}

void PinExpansion::setup()
{
    this->pcf.begin();
}

void PinExpansion::setInputListener(int pin, PinUpdateListener listener)
{
    this->listeners[pin] = listener;
}

#define PIN_DATA(d, p) (d & (1 << p)) ? 1 : 0

void PinExpansion::loop()
{
    static unsigned long start = millis();
    unsigned long elapsed = millis() - start;
    uint8_t data;

    if (elapsed > PCF_UPDATE_RATE && this->last != (data = this->pcf.read8()))
    {

        enum PinState *result = (enum PinState *)malloc(sizeof(enum PinState) * 8);

        for (int bit = 0; bit < 8; bit++)
        {
            int oldval = PIN_DATA(this->last, bit);
            int newval = PIN_DATA(data, bit);

            if (oldval == 0 && newval == 1)
                result[bit] = PIN_RISING;
            else if (oldval == 1 && newval == 0)
                result[bit] = PIN_FALLING;
            else if (oldval == newval == 0)
                result[bit] = PIN_KEPT_LOW;
            else
                result[bit] = PIN_KEPT_HIGH;

            if (this->listeners[bit] != NULL && (result[bit] & (PIN_RISING | PIN_FALLING)))
            {
                this->listeners[bit](result[bit]);
            }
        }

        if (this->onUpdated)
            this->onUpdated(result);

        this->last = data;

        Serial.printf("pins = %02X %02X   %d %d %d %d   %d %d %d %d\n", data, this->last, PIN_DATA(data, 0), PIN_DATA(data, 1), PIN_DATA(data, 2), PIN_DATA(data, 3), PIN_DATA(data, 4), PIN_DATA(data, 5), PIN_DATA(data, 6), PIN_DATA(data, 7));
        start = millis();
    }
}

int PinExpansion::getData(int pin)
{
    return 0;
}
