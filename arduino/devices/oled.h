#ifndef __OLED_H
#define __OLED_H

#include "device.h"
#include <Adafruit_SSD1306.h>

/**
 * Controls the OLED 0.91" I2C interface.
 * Official name is SSD1306
 */
class Oled : public Device
{
public:
    Oled(int addr = 0x3C, int w = 128, int h = 32);
    virtual void setup();
    virtual void loop();
    Adafruit_SSD1306 &getOled() { return this->oled; }

    // Utility draw for Yellow-Blue 128 x 64 display
    void setBlueText(String text);
    void setYellowText(String text, bool inverse = false);
    void setScreenText(String mainText, String titleText);

private:
    int addr;
    Adafruit_SSD1306 oled;
};

#include "oled.cpp"

#endif