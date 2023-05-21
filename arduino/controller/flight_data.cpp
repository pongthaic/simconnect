#include "flight_data.h"
#include <map>

FlightData::FlightData()
{
    this->displayMode = this->displayData.begin();
    this->inputMode = this->inputData.begin();
}

bool FlightData::operator==(FlightData &other)
{
    if (this == &other)
        return true;

    for (DataEntry::iterator it = this->inputData.begin(); it != this->inputData.end(); it++)
    {
        if (it->second != other.inputData[it->first])
            return false;
    }

    for (DataEntry::iterator it = this->displayData.begin(); it != this->displayData.end(); it++)
    {
        if (it->second != other.displayData[it->first])
            return false;
    }

    return true;
}

bool FlightData::operator!=(FlightData &other)
{
    return !(other == *this);
}

bool FlightData::available()
{
    return !this->inputData.empty() || !this->displayData.empty();
}

String FlightData::nextDisplay()
{
    if (!this->displayData.empty())
    {
        this->displayMode++;
        if (this->displayMode == this->displayData.end())
            this->displayMode = this->displayData.begin();
        return this->displayMode->first;
    }
    else
    {
        return "Empty";
    }
}

String FlightData::nextInput()
{
    this->inputMode++;
    if (this->inputMode == this->inputData.end())
        this->inputMode = this->inputData.begin();
    return this->inputMode->first;
}

String FlightData::toString()
{
    String result("");
    DataEntry::iterator it1 = this->displayData.begin();
    for (; it1 != this->displayData.end(); it1++)
    {
        result += it1->first;
        result += "=";
        result += it1->second;
        result += "\n";
    }

    DataEntry::iterator it2 = this->inputData.begin();
    for (; it2 != this->inputData.end(); it2++)
    {
        result += it2->first;
        result += "=";
        result += it2->second;
        result += "\n";
    }

    return result;
}

String FlightData::displayTitle()
{
    return this->displayMode->first;
}

String FlightData::displayValue()
{
    return this->displayMode->second;
}

String FlightData::inputTitle()
{
    return this->inputMode->first;
}

String FlightData::inputValue()
{
    return this->inputMode->second;
}