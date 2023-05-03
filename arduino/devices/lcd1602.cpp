#include "lcd1602.h"
#include <stdarg.h>
#include <LiquidCrystal_I2C.h>

LCD1602::LCD1602(int _addr) : lcd(_addr, 16, 2)
{
    this->addr = _addr;
    this->lcd.begin();
}

void LCD1602::setup()
{
    this->lcd.clear();
    this->lcd.backlight();
}

void LCD1602::loop()
{
}
