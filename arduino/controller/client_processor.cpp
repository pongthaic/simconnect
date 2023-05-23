#include <ESP8266WiFi.h>
#include <malloc.h>
#include <vector>
#include <map>

#include "parser.h"
#include "flight_data.h"

typedef std::map<String, String> PayloadData;

#define DISPLAY_DATA 0
#define INPUT_DATA 1

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
void onClientDataReceived(WiFiClient *client, String data)
{
    auto args = _split(data, " ");

    if (args[0] == "D")
    {
        flightData.displayData[args[1]] = args[2];
    }
    else if (args[0] == "I")
    {
        flightData.inputData[args[1]] = args[2];
    }
    else if (args[0] == "N")
    {
        flightData.nonDisplayData[args[1]] = args[2];
    }

    /*

    int eq = data.indexOf('=');

    if (eq >= 0)
    {
        // data mode
        String key = data.substring(0, data.indexOf('='));
        String val = data.substring(data.indexOf('=') + 1);

        Serial.printf("%s is %s\n", key, val);
        flightData.inputData[key] = val;
    }
    else
    {
        // Command mode
        data.trim();
        if (data == "GET")
        {
            client->println(flightData.toString());
            client->flush();
        }
    }
    */
}

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