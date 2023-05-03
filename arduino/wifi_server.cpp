#include "ESP8266WiFi.h"

void _initWifi()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    int dots = 0;

    while (WiFi.status() != WL_CONNECTED)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Connecting");
        lcd.setCursor(10, 0);
        for (int i = 0; i < dots % 5; i++)
        {
            lcd.print(F("."));
        }
        dots++;
        delay(500);
    }
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print(F("connected"));
}

void _initServer()
{
    lcd.setCursor(0, 0);
    lcd.print(WiFi.localIP());
    svr.begin();
}

void _acceptWiFiClient()
{
    WiFiClient client = svr.accept();
    if (!client)
    {
        return;
    }
    String req = client.readStringUntil('\r');
    int qindex = req.indexOf('?');

    if (qindex > 0)
    {
        String queries = req.substring(qindex + 1);
        lcd.setCursor(0, 1);
        lcd.print(queries);
        Serial.println(queries);
    }

    _printStates(client);
    client.flush();
}