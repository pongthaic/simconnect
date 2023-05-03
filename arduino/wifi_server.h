#ifndef __WIFI_H
#define __WIFI_H

class WebServer
{
public:
    WebServer(int port = 8080);
    void begin();
    void dispatch();
};

#include "wifi_server.cpp"

#endif