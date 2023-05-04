#include <ESP8266WiFi.h>

WebServer::WebServer(const char *ssid, const char *password, int port) : port(port)
{
    WiFi.mode(WIFI_STA);
    this->ssid = ssid;
    this->password = password;
}

void WebServer::setup()
{
    // Connect to Wifi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        if (this->onConnecting != NULL)
            this->onConnecting();
        delay(1000);
    }
    if (this->onConnected != NULL)
        this->onConnected(WiFi.localIP().toString());

    // Initialize Server
    this->svr = new WiFiServer(this->port);
}

void WebServer::loop()
{
    WiFiClient client = this->svr->available();
    if (client)
    {
        if (this->onClientConnected != NULL)
        {
            String request = client.readString();
            this->onClientConnected(&client, request);
        }

        String data = this->onClientDataRequest != NULL ? this->onClientDataRequest(&client) : "{}";
        client.write("HTTP/1.1 200 OK\r\n");
        client.write("Content-Type: application/json\r\n");
        client.write("\r\n");

        client.write(data.c_str());
        client.flush();
    }
}

bool WebServer::isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}
