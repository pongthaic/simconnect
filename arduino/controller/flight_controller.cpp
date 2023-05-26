
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
    if (!flightData.available())
        return;

    String newVal;

    switch (flightData.currentEntry(DATAENTRY_ROLE_INPUT).type)
    {
    case DATAENTRY_TYPE_FREQ_VOR:
        newVal = _handleFreqChange(detents, flightData.currentValue(DATAENTRY_ROLE_INPUT), 2, 10800, 11800, 5);
        break;
    case DATAENTRY_TYPE_FREQ_COM:
        newVal = _handleFreqChange(detents, flightData.currentValue(DATAENTRY_ROLE_INPUT), 3, 118000, 136975, 25);
        break;
    case DATAENTRY_TYPE_UINT_ALT:
        newVal = _handleNumericChange(detents, flightData.currentValue(DATAENTRY_ROLE_INPUT), 0, 50000, 100, false);
        break;
    case DATAENTRY_TYPE_UINT_HDG:
        newVal = _handleNumericChange(detents, flightData.currentValue(DATAENTRY_ROLE_INPUT), 1, 360, 1, true);
        break;
    case DATAENTRY_TYPE_UINT_SPD:
        newVal = _handleNumericChange(detents, flightData.currentValue(DATAENTRY_ROLE_INPUT), 0, 400, 1, false);
        break;
    case DATAENTRY_TYPE_INT_VSPD:
        newVal = _handleNumericChange(detents, flightData.currentValue(DATAENTRY_ROLE_INPUT), 0, -5000, 5000, false);
        break;
    default:
        newVal = _handleNumericChange(detents, flightData.currentValue(DATAENTRY_ROLE_INPUT), 0, 1000000, 1, false);
    }

    flightData.setValue(DATAENTRY_ROLE_INPUT, newVal);
}

void FlightController::rotateTrim(int detents)
{
}

/**
 * decimalPlaces - number of digits displayed.
 * steps - the coefficient applied to each step of detent, corresponded to decimal places. For example, 1 decimal place
 * with 5 steps makes 1.0 goes to 1.5, 2.0 while 3 decimal places with 25 step makes 1.000 goes to 1.025, 1.050 accordingly.
 *
 * For frequency handling, upon overflow, the number reverts.
 */
inline String _handleFreqChange(int detents, String originalValue, int decimalPlaces, int min, int max, int steps)
{
    originalValue.remove(decimalPlaces + 1, 1); // remove dots
    int value = originalValue.toInt();
    value += detents * steps;

    if (value > 11795)
        value = 10800;
    else if (value < 10800)
        value = 11795;

    char *newstr = (char *)malloc(sizeof(char) * 7);
    snprintf(newstr, 8, "%03d.%02d", (int)floor(value / 100.0f), value % 100);
    String ret(newstr);
    free(newstr);
    return ret;
}

/**
 * For numeric handling, upon limit reached, the number stucks at limits if cycleOnOverflow = false, reverted to another end
 * if this flag is true.
 */
inline String _handleNumericChange(int detent, String originalValue, int min, int max, int steps, bool cycleOnOverflow)
{
    int value = originalValue.toInt();
    value += detent * steps;
    if (value > max)
    {
        if (cycleOnOverflow)
            value = min;
        else
            value = max;
    }
    else if (value < min)
    {
        if (cycleOnOverflow)
            value = max;
        else
            value = min;
    }
    return String(value);
}

enum ButtonNo
{
    BUTTON_NEXT_INPUT = 1,
    BUTTON_NEXT_DISPLAY = 2,
    BUTTON_PRECISION_INPUT = 7,
};

void FlightController::pressButton(int buttonNo)
{
    if (buttonNo == BUTTON_NEXT_INPUT)
    {
        flightData.next(DATAENTRY_ROLE_INPUT);
    }
    else if (buttonNo == BUTTON_NEXT_DISPLAY)
    {
        flightData.next(DATAENTRY_ROLE_DISPLAY);
    }
}