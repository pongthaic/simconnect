#ifndef __FLIGHT_DATA_H
#define __FLIGHT_DATA_H

#include <map>
#include <vector>

typedef enum DataEntryRoleEnum
{
    DATAENTRY_ROLE_DISPLAY,
    DATAENTRY_ROLE_INPUT,
    DATAENTRY_ROLE_NONDISPLAY,

    DATAENTRY_ROLE_MAX,
} DataEntryRole;

typedef enum DataEntryTypeEnum
{
    DATAENTRY_TYPE_FREQ_VOR,
    DATAENTRY_TYPE_FREQ_COM,
    DATAENTRY_TYPE_FREQ_NDB,
    DATAENTRY_TYPE_UINT_DME,
    DATAENTRY_TYPE_UINT_ALT,
    DATAENTRY_TYPE_UINT_SPD,
    DATAENTRY_TYPE_INT_VSPD,
    DATAENTRY_TYPE_UINT_HDG, // and course
    DATAENTRY_TYPE_INT_TRIM,
} DataEntryType;

typedef struct DataEntryStruct
{
    String value;
    DataEntryRole role;
    DataEntryType type;
} DataEntry;

typedef std::map<String, DataEntry> DataBase;

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

    bool available();

    /** Call upon initialization of client connectivity */
    void setupEntry(String label, String initialValue, DataEntryRole role, DataEntryType type);

    String currentLabel(DataEntryRole role);

    String currentValue(DataEntryRole role);

    DataEntry &currentEntry(DataEntryRole role);

    void next(DataEntryRole role);

    String toString();

protected:
    DataBase _db[3];
    DataBase::iterator _dbit[3];
};

/** singleton global */
FlightData flightData;

#include "flight_data.cpp"

#endif