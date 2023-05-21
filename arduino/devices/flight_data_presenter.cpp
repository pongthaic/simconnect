#include "flight_data_presenter.h"

#define LCD_UPDATE_INTERVAL 100

FlightDataPresenter::FlightDataPresenter(LCD1602 &lcd, PinExpansion &px, Oled &oled, FlightData &fd)
    : lcd(lcd), px(px), oled(oled), flightData(fd)
{
}

void FlightDataPresenter::setup()
{
    _updateLCD();
}

void FlightDataPresenter::loop()
{
    static String displayTitle = String("-");
    static String displayValue = String("-");
    static String inputTitle = String("-");
    static String inputValue = String("-");

    static unsigned long lastUpdated = millis();

    if (millis() - lastUpdated < LCD_UPDATE_INTERVAL)
        return;

    if (displayValue != this->flightData.displayValue() || inputValue != this->flightData.inputValue() || displayTitle != this->flightData.displayTitle() || inputTitle != this->flightData.inputTitle())
    {
        displayTitle = this->flightData.displayTitle();
        displayValue = this->flightData.displayValue();
        inputTitle = this->flightData.inputTitle();
        inputValue = this->flightData.inputValue();

        this->_updateLCD();
    }
}

void FlightDataPresenter::_updateLCD()
{
    if (!this->flightData.available())
    {
        this->lcd.lcd.setCursor(0, 1);
        this->lcd.lcd.print("ready >>");
        return;
    }
    else
    {
        if (!this->flightData.inputData.empty())
        {
            if (this->flightData.inputMode == this->flightData.inputData.end())
                this->flightData.nextInput();

            this->lcd.lcd.clear();
            this->lcd.lcd.setCursor(0, 0);
            this->lcd.lcd.print(this->flightData.inputTitle());
            this->lcd.lcd.setCursor(0, 1);
            this->lcd.lcd.print(this->flightData.inputValue());
        }

        if (!this->flightData.displayData.empty())
        {
            if (this->flightData.displayMode == this->flightData.displayData.end())
                this->flightData.nextDisplay();

            this->lcd.lcd.setCursor(8, 0);
            this->lcd.lcd.print(this->flightData.displayTitle());
            this->lcd.lcd.setCursor(8, 1);
            this->lcd.lcd.print(this->flightData.displayValue());
        }
    }
}