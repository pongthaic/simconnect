#include "devices/device.h"
#include "devices/lcd1602.h"
#include "devices/pin_expansion.h"
#include "devices/rotary.h"
#include <stdlib.h>
#include <Arduino.h>

LCD1602 lcd;
PinExpansion expn;
RotaryEncoder knob1(12, 13);

int lastValue = 0;

void setup()
{
    Serial.begin(15200);
    lcd.setup();
    expn.setup();
    knob1.setup();
    lcd.lcd.setCursor(0, 0);
    lcd.lcd.printf("Welcome.");
}

void loop()
{
    if (knob1.value != lastValue)
    {
        lcd.lcd.setCursor(0, 0);
        lcd.lcd.printf("Value is %d, detents = %d", knob1.value, knob1.detents);
        lastValue = knob1.value;
    }
}