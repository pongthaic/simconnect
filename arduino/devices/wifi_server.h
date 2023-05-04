#ifndef __WEB_SERVER_H
#define __WEB_SERVER_H

#include "device.h"
#include <ESP8266WiFi.h>

class WebServer : public Device
{
public:
    WebServer(const char *ssid, const char *password, int port = 80);
    virtual void setup();
    virtual void loop();

    bool isConnected();

    void (*onConnecting)() = NULL;
    void (*onConnected)(String localIp) = NULL;
    void (*onClientConnected)(WiFiClient *client, String request) = NULL;
    String (*onClientDataRequest)(WiFiClient *client) = NULL;

private:
    const char *ssid;
    const char *password;
    const int port;
    WiFiServer *svr;
};

#include "wifi_server.cpp"

#endif