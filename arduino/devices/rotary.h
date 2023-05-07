#ifndef __ROTARY_H
#define __ROTARY_H

#include "./device.h"

class RotaryEncoder : public Device
{
public:
    RotaryEncoder(int clk, int dt);
    void setup();
    void loop();

    void (*onValueChanged)(int newVal, int oldVal) = NULL;

    volatile int value;
    volatile int clk;
    volatile int dt;
    volatile int lastClk;
    volatile int detents;

private:
    int lastValue = 0;
};

#include "./rotary.cpp"

#endif