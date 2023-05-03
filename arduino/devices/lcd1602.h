#include <LiquidCrystal_I2C.h>
#include "./device.h"

#ifndef __LCD1602
#define __LCD1602

#define LCD_ADDR 0x27

class LCD1602 : Device
{
public:
    LCD1602(int clockPin, int dataPin);
    virtual void setup();
    virtual void loop();

    void printf(const char *format, ...);

private:
    LiquidCrystal_I2C lcd;
};

#include "./lcd1602.cpp"

#endif