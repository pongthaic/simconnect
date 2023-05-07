#include <ESP8266WiFi.h>
#include <malloc.h>
#include <map>

#include "parser.h"
#include "flight_data.h"

typedef std::map<String, String> PayloadData;

#define DISPLAY_DATA 0
#define INPUT_DATA 1

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

String onClientDataRequest(WiFiClient *client)
{
    return flightData.toString();
}
