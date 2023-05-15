#ifndef __FLIGHT_DATA_PRESENTER
#define __FLIGHT_DATA_PRESENTER

#include "../controller/flight_data.h"
#include "device.h"

#include "lcd1602.h"
#include "oled.h"
#include "pin_expansion.h"

class FlightDataPresenter : public Device
{
public:
    FlightDataPresenter(LCD1602 &lcd, PinExpansion &px, Oled &oled, FlightData &fd);
    virtual void setup();
    virtual void loop();

protected:
    LCD1602 &lcd;
    PinExpansion &px;
    Oled &oled;
    FlightData &flightData;

private:
    void _updateLCD();
};

#include "flight_data_presenter.cpp"

#endif