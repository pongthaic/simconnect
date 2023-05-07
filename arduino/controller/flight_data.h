#ifndef __FLIGHT_DATA_H
#define __FLIGHT_DATA_H

#include <map>
#include <vector>

typedef std::map<String, String> DataEntry;

/**
 * Model class that represents the current state of an active flight.
 *
 * The display of the Dashboard are on two components:
 * - LCD    => Displaying the flight 'Input', i.e. radio frequencies and
 * - OLED   => Displaying the flight 'Display', i.e. DME, alt, airspeed, etc.
 */
class FlightData
{
public:
    FlightData();
    String nextDisplay();
    String nextInput();

    String displayTitle();
    String displayValue();

    String inputTitle();
    String inputValue();

    String toString();

    DataEntry displayData;
    DataEntry inputData;

    DataEntry::iterator displayMode;
    DataEntry::iterator inputMode;
};

/** singleton global */
FlightData flightData;

#include "flight_data.cpp"

#endif