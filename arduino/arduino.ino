#include "devices/device.h"
#include "devices/lcd1602.h"
#include <stdlib.h>

LCD1602 lcd(13, 12);

void setup()
{
    Serial.begin(115200);
    Serial.printf("Initialized.");
    lcd.setup();
}

void loop()
{
    lcd.loop();
}