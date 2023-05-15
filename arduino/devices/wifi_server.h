#ifndef __WEB_SERVER_H
#define __WEB_SERVER_H

#include "device.h"
#include <ESP8266WiFi.h>

class WebServer : public Device
{
public:
    WebServer(String ssid, String password, int port = 80);
    virtual ~WebServer();
    virtual void setup();
    virtual void loop();

    bool isConnected();

    void (*onConnecting)() = NULL;
    void (*onConnected)(String localIp) = NULL;
    void (*onClientConnected)(WiFiClient *client, String request) = NULL;
    String (*onClientDataRequest)(WiFiClient *client) = NULL;

protected:
    String ssid;
    String password;
    const int port;
    WiFiServer *svr;
};

#include "wifi_server.cpp"

#endif