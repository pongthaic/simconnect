#include "devices/device.h"
#include "devices/lcd1602.h"
#include "devices/pin_expansion.h"
#include "devices/rotary.h"
#include "devices/wifi_server.h"
#include "devices/oled.h"
#include "devices_container.h"

#include "controller/client_processor.h"

#include <stdlib.h>
#include <Arduino.h>

LCD1602 lcd;
PinExpansion expn;
RotaryEncoder knob1(12, 13);
RotaryEncoder knob2(14, 2);
Oled oled(0x3C, 128, 64);
DeviceContainer devices;
WebServer websvr("udomsuk_downstairs_24", "chandpoung");
int lastValue = 0;
int lastValue2 = 0;

void setup()
{
    websvr.onConnecting = onWebServerConnecting;
    websvr.onConnected = onWebServerConnected;
    websvr.onClientConnected = onClientConnected;
    websvr.onClientDataRequest = onClientDataRequest;

    devices.addDevice(lcd);
    devices.addDevice(expn);
    devices.addDevice(knob1);
    devices.addDevice(knob2);
    devices.addDevice(websvr);
    devices.addDevice(oled);

    Serial.begin(115200);
    devices.setup();
    expn.pcf.write(0, HIGH);

    oled.setYellowText("Connecting");
    oled.getOled().display();
}

void loop()
{
    devices.loop();

    if (knob1.value != lastValue || knob2.value != lastValue2)
    {
        lcd.lcd.setCursor(0, 1);
        lcd.lcd.printf("V1: %3d, V2: %3d", knob1.value, knob2.value);
        lastValue = knob1.value;
        lastValue2 = knob2.value;
    }

    _updateOLEDDisplay();
}

void onWebServerConnecting()
{
    static int dots = 0;
    lcd.lcd.clear();
    lcd.lcd.setCursor(0, 0);
    lcd.lcd.print("Connecting");
    for (int i = 0; i < dots; i++)
    {
        lcd.lcd.print(".");
    }
    dots++;
    if (dots > 3)
        dots = 0;
}

void onWebServerConnected(String ip)
{
    lcd.lcd.clear();
    lcd.lcd.printf("IP: %s", ip);
}

void _updateOLEDDisplay()
{
    static unsigned long lastRefresh = millis();

    if (millis() - lastRefresh > 100)
    {
        oled.setScreenText(String(knob1.value), "VOR1");
        lastRefresh = millis();
    }
}

void _serialScan()
{
    byte error, address;
    int nDevices;
    Serial.println("Scanning...");
    nDevices = 0;
    for (address = 1; address < 127; address++)
    {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if (error == 0)
        {
            Serial.print("I2C device found at address 0x");
            if (address < 16)
            {
                Serial.print("0");
            }
            Serial.println(address, HEX);
            nDevices++;
        }
        else if (error == 4)
        {
            Serial.print("Unknow error at address 0x");
            if (address < 16)
            {
                Serial.print("0");
            }
            Serial.println(address, HEX);
        }
    }
    if (nDevices == 0)
    {
        Serial.println("No I2C devices found\n");
    }
    else
    {
        Serial.println("done\n");
    }
    delay(5000);
}
