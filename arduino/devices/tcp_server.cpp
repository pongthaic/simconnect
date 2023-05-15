#include <ESP8266WiFi.h>
#include "tcp_server.h"
#include <vector>

TCPServer::TCPServer(String ssid, String password, int port) : WebServer(ssid, password, port)
{
    WiFi.mode(WIFI_STA);
}

TCPServer::~TCPServer()
{
    while (!this->clients.empty())
    {
        std::vector<WiFiClient>::iterator it = this->clients.begin();
        it->stop();
        const String ip = it->remoteIP().toString();
        this->clients.erase(it);
        Serial.printf("disconnected client from %s\n", ip);
    }
}

void TCPServer::loop()
{
    WiFiClient c = this->svr->available();
    if (c)
    {
        this->clients.push_back(c);
    }

    for (std::vector<WiFiClient>::iterator it = this->clients.begin(); it != this->clients.end(); it++)
    {
        WiFiClient &client = *it;
        if (client.available())
        {
            String received = client.readStringUntil('\n');
            Serial.printf("received '%s' from client %s\n", received, client.remoteIP().toString());

            if (received == "$close\n")
            {
                Serial.printf("client %s disconnected.\n", client.remoteIP().toString());
                client.flush();
                client.stop(); // disconnect.
                this->clients.erase(it);
            }
            else
            {
                if (this->onReceived != NULL)
                {
                    onReceived(&client, received);
                }
            }
        }
    }
}