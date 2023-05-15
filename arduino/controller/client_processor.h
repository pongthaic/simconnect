#ifndef __CLIENT_PROCESSOR_H
#define __CLIENT_PROCESSOR_H

#include <ESP8266WiFi.h>

void onClientConnected(WiFiClient *client, String request);
String onClientDataRequest(WiFiClient *client);
void onClientDataReceived(WiFiClient *client, String data);

#include "client_processor.cpp"

#endif