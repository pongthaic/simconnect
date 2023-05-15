#include "flight_data_presenter.h"

FlightDataPresenter::FlightDataPresenter(LCD1602 &lcd, PinExpansion &px, Oled &oled, FlightData &fd)
    : lcd(lcd), px(px), oled(oled), flightData(fd)
{
}

void FlightDataPresenter::setup()
{
}

void FlightDataPresenter::loop()
{
    static FlightData lastData(this->flightData);

    if (this->flightData != lastData)
        this->_updateLCD();
}

void FlightDataPresenter::_updateLCD()
{
    if (!this->flightData.available())
    {
        return;
    }
    this->lcd.lcd.clear();
    this->lcd.lcd.setCursor(0, 0);
    this->lcd.lcd.print((this->flightData.displayMode)->first);
    this->lcd.lcd.setCursor(0, 1);
    this->lcd.lcd.print((this->flightData.displayMode)->second);
}