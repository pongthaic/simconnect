#include <ESP8266WiFi.h>
#include <malloc.h>
#include <vector>
#include <map>

#include "parser.h"
#include "flight_data.h"

typedef std::map<String, String> PayloadData;

/**
 * The Protocol
 *
 * Command
 * -------
 * <command> [<arg1>] [<arg2>] ...\n
 *
 *

 * List of Commands
 * ----------------
 * Client --> Server
 * D   Update DISPLAY values
 * e.g. D DME 110
 *
 * I   Update INPUT values
 * e.g. I VOR1 117.70
 *
 * N  Update Non-Displayable Inputs
 * N  LANDING_GEAR 0
 *
 * G
 * Get the current stored values
 * Result:
 * D <key> <value>\n
 * I <key> <value>\n
 * N <key> <value>\n
 * ...
 * \n
 *
 *
 * Server --> Client
 *
 * D <key> <value>\n
 * I <key> <value>\n
 * N <key> <value>\n
 *
 * G
 * Get the current state of flight
 *
 *
 *
 *
*/

#define _COMMAND(cmd, n_args) else if (args.size() > n_args && args[0] == cmd)

void onClientDataReceived(WiFiClient *client, String data)
{
    auto args = _split(data, " ");

    if (args.size() == 0)
    {
        // empty command - valid no-op.
        return;
    }

    _COMMAND("S", 4)
    flightData.setupEntry(args[1], args[2], _stringToRole(args[3]), _stringToType(args[4]));

    _COMMAND("D", 2)
    flightData.setValue(DATAENTRY_ROLE_DISPLAY, args[1], args[2]);

    _COMMAND("I", 2)
    flightData.setValue(DATAENTRY_ROLE_INPUT, args[1], args[2]);

    _COMMAND("N", 2)
    flightData.setValue(DATAENTRY_ROLE_NONDISPLAY, args[1], args[2]);

    else
    {
        Serial.printf("invalid command %s with %d arguments.\n", args[0], args.size());
    }
}

#undef _COMMAND

String onClientDataRequest(WiFiClient *client)
{
    return flightData.toString();
}

std::vector<String> _split(String &data, String delim = " ")
{
    std::vector<String> args;

    uint spc = data.indexOf(delim);
    uint i = 0;

    while (spc >= 0)
    {
        args.push_back(data.substring(i, spc));
        i += spc + 1;
        spc = data.indexOf(delim, i);
    }

    return args;
}

DataEntryRole _stringToRole(String input)
{
    if (input == "DISPLAY")
        return DATAENTRY_ROLE_DISPLAY;
    else if (input == "INPUT")
        return DATAENTRY_ROLE_INPUT;
    else if (input == "NONDISPLAY")
        return DATAENTRY_ROLE_NONDISPLAY;

    return DATAENTRY_ROLE_DISPLAY;
}

DataEntryType _stringToType(String input)
{
    if (input == "VOR")
        return DATAENTRY_TYPE_FREQ_VOR;
    else if (input == "COM")
        return DATAENTRY_TYPE_FREQ_COM;
    else if (input == "NDB")
        return DATAENTRY_TYPE_FREQ_NDB;
    else if (input == "DME")
        return DATAENTRY_TYPE_UINT_DME;
    else if (input == "ALT")
        return DATAENTRY_TYPE_UINT_ALT;
    else if (input == "SPD")
        return DATAENTRY_TYPE_UINT_SPD;
    else if (input == "VSPD")
        return DATAENTRY_TYPE_INT_VSPD;
    else if (input == "HDG")
        return DATAENTRY_TYPE_UINT_HDG;
    else if (input == "TRIM")
        return DATAENTRY_TYPE_INT_TRIM;

    return DATAENTRY_TYPE_FREQ_VOR;
}