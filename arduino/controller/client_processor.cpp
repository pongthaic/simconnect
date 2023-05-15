#include <ESP8266WiFi.h>
#include <malloc.h>
#include <map>

#include "parser.h"
#include "flight_data.h"

typedef std::map<String, String> PayloadData;

#define DISPLAY_DATA 0
#define INPUT_DATA 1

// OBSOLETED
void onClientConnected(WiFiClient *client, String request)
{
    Serial.println("Client Connected.");
    PayloadData data = parseRequest(request);
    PayloadData::iterator it = data.begin();
    int mode = DISPLAY_DATA;

    if (data["_PATH"] == "display")
        mode = DISPLAY_DATA;
    else
        mode = INPUT_DATA;

    for (; it != data.end(); it++)
    {
        if (it->first != "_PATH")
        {
            if (mode == DISPLAY_DATA)
                flightData.displayData[it->first] = it->second;
            else
                flightData.inputData[it->first] = it->second;
        }
    }

    // remove after debug
    flightData.inputMode = flightData.inputData.begin();
}

void onClientDataReceived(WiFiClient *client, String data)
{
    int eq = data.indexOf('=');

    if (eq >= 0)
    {
        // data mode
        String key = data.substring(0, data.indexOf('='));
        String val = data.substring(data.indexOf('=') + 1);

        Serial.printf("%s is %s\n", key, val);
        flightData.displayData[key] = val;
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
}

String onClientDataRequest(WiFiClient *client)
{
    return flightData.toString();
}
