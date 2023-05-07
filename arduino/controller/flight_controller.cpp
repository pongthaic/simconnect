
#include "flight_controller.h"
#include "flight_data.h"

#include <malloc.h>

FlightController::FlightController()
{
}

void FlightController::turnSwitch(int switchNo, bool on)
{
}

void FlightController::rotateKnob(int detents, int pushState)
{
    if (flightData.inputTitle().startsWith("VOR"))
    {
        String target = flightData.inputTitle();
        String current = flightData.inputValue();
        current.remove(3, 1); // remove dot
        int value = current.toInt();

        if (pushState != 0)
            value += detents * 100;
        else
            value += detents * 5;

        if (value > 11795)
            value = 10800;
        else if (value < 10800)
            value = 11795;

        char *newstr = (char *)malloc(sizeof(char) * 7);
        snprintf(newstr, 8, "%03d.%02d", (int)floor(value / 100.0f), value % 100);

        flightData.inputData[target] = String(newstr);
        free(newstr);

        Serial.println(flightData.inputData[target]);
    }
}

void FlightController::rotateTrim(int detents)
{
}

void FlightController::pressButton(int buttonNo)
{
}