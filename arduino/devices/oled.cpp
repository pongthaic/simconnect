#include "oled.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMono9pt7b.h>
#include <Fonts/FreeMono12pt7b.h>
#include <Fonts/FreeMono18pt7b.h>

Oled::Oled(int addr, int w, int h) : addr(addr), oled(w, h, &Wire, -1)
{
    this->oled.setFont(&FreeMono18pt7b);
}

void Oled::setup()
{
    if (!this->oled.begin(SSD1306_SWITCHCAPVCC, this->addr))
    {
        Serial.println("OLED startup failed.");
    }
    else
    {
        Serial.println("OLED Setup succeeded.");
        this->oled.clearDisplay();
    }
}

void Oled::loop()
{
}

void Oled::setBlueText(String text)
{
    this->oled.setCursor(0, 62);
    this->oled.setTextColor(INVERSE);
    this->oled.setFont(&FreeMono18pt7b);
    this->oled.print(text.c_str());
}

void Oled::setYellowText(String text, bool inverse)
{
    // this->oled.fillRect(10, 10, 120, 16, WHITE);
    // this->oled.fillRect(1, 1, 50, 10, WHITE);
    this->oled.setCursor(0, 13);
    this->oled.setTextColor(WHITE);
    this->oled.setFont(&FreeMono9pt7b);
    this->oled.print(text.c_str());
}

/*
this->oled.begin(SSD1306_SWITCHCAPVCC, this->addr);
    this->oled.clearDisplay();
    this->oled.setCursor(0, 0);
    this->oled.print("Hello");
    this->oled.drawLine(0, 0, 16, 16, WHITE);
    this->oled.display();
*/