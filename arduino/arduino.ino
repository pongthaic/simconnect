#include "devices/device.h"
#include "devices/lcd1602.h"
#include "devices/pin_expansion.h"
#include "devices/rotary.h"
#include "devices/wifi_server.h"
#include "devices_container.h"

#include <stdlib.h>
#include <Arduino.h>

LCD1602 lcd;
PinExpansion expn;
RotaryEncoder knob1(12, 13);
RotaryEncoder knob2(14, 2);
DeviceContainer devices;
WebServer websvr("udomsuk_downstairs_24", "chandpoung");
int lastValue = 0;
int lastValue2 = 0;

void setup()
{
    websvr.onConnecting = onWebServerConnecting;
    websvr.onConnected = onWebServerConnected;

    devices.addDevice(lcd);
    devices.addDevice(expn);
    devices.addDevice(knob1);
    devices.addDevice(knob2);
    devices.addDevice(websvr);

    Serial.begin(15200);
    devices.setup();
}

void loop()
{
    devices.loop();

    if (knob1.value != lastValue || knob2.value != lastValue2)
    {
        lcd.lcd.setCursor(0, 1);
        lcd.lcd.printf("V1: %d, V2: %d", knob1.value, knob2.value);
        lastValue = knob1.value;
        lastValue2 = knob2.value;
    }
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