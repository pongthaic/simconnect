#include "lcd1602.h"
#include <stdarg.h>

LCD1602::LCD1602(int _clockPin, int _dataPin) : lcd(LCD_ADDR, 16, 2)
{
    pinMode(_clockPin, OUTPUT);
    pinMode(_dataPin, OUTPUT);
}

void LCD1602::setup()
{
}

void LCD1602::loop()
{
}

void LCD1602::printf(const char *format, ...)
{
}
