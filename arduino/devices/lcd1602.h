#include <LiquidCrystal_I2C.h>
#include "./device.h"

#ifndef __LCD1602
#define __LCD1602

#define LCD_ADDR 0x27

class LCD1602 : public Device
{
public:
    /**
     * Initialize the LCD1602 module.
     */
    LCD1602(int addr = LCD_ADDR);
    virtual void setup();
    virtual void loop();

    void printf(int col, int row, const char *format, ...);
    LiquidCrystal_I2C lcd;
    int addr;
};

#include "./lcd1602.cpp"

#endif