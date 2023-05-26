#include "flight_data.h"
#include <map>

FlightData::FlightData()
{
    for (int role = 0; role < DATAENTRY_ROLE_MAX; role++)
    {
        this->_dbit[role] = this->_db[role].begin();
    }
}

void FlightData::setupEntry(String label, String initialValue, DataEntryRole role, DataEntryType type)
{
    DataEntry ent;
    ent.role = role;
    ent.type = type;
    ent.value = initialValue;

    this->_db[role][label] = ent;
}

String FlightData::currentLabel(DataEntryRole role)
{
    if (this->_dbit[role] == this->_db[role].end())
        return "-";

    return this->_dbit[role]->first;
}

String FlightData::currentValue(DataEntryRole role)
{
    if (this->_dbit[role] == this->_db[role].end())
        return "-";
    return this->_dbit[role]->second.value;
}

void FlightData::setValue(DataEntryRole role, String value)
{
    this->_dbit[role]->second.value = value;
}

void FlightData::setValue(DataEntryRole role, String value, String key)
{
    if (this->_db[role].find(key) == this->_db[role].end())
    {
        Serial.printf("error: no %s setup for role %d.\n", key, role);
        return;
    }

    this->_db[role][key].value = value;
}

DataEntry &FlightData::currentEntry(DataEntryRole role)
{
    return this->_dbit[role]->second;
}

void FlightData::next(DataEntryRole role)
{
    this->_dbit[role]++;
    if (this->_dbit[role] == this->_db[role].end())
        this->_dbit[role] = this->_db[role].begin();
}

bool FlightData::available()
{
    for (int role = 0; role < DATAENTRY_ROLE_MAX; role++)
    {
        if (this->_db[role].begin() == this->_db[role].end())
            return false;
    }
    return true;
}

String FlightData::toString()
{
    String result("");
    for (int role = 0; role < DATAENTRY_ROLE_MAX; role++)
    {
        for (auto it1 = this->_db[role].begin(); it1 != this->_db[role].end(); it1++)
        {
            result += it1->first;
            result += "=";
            result += it1->second;
            result += "\n";
        }
    }

    return result;
}