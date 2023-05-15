#ifndef __TCP_SERVER_H
#define __TCP_SERVER_H

#include "device.h"
#include "wifi_server.h"

#include <vector>

class TCPServer : public WebServer
{
public:
    TCPServer(String ssid, String password, int port = 8779);
    virtual ~TCPServer();
    virtual void loop();

    void (*onReceived)(WiFiClient *client, String data) = NULL;

private:
    std::vector<WiFiClient> clients;

    int port;
    String ssid;
    String password;
};

#include "tcp_server.cpp"
#endif