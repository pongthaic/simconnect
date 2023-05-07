#include "devices/device.h"
#include "devices/lcd1602.h"
#include "devices/pin_expansion.h"
#include "devices/rotary.h"
#include "devices/wifi_server.h"
#include "devices/oled.h"
#include "devices_container.h"

#include "controller/client_processor.h"
#include "controller/flight_controller.h"
#include "controller/flight_data.h"

#include <stdlib.h>
#include <Arduino.h>

#define EXPN_KNOB_PIN 1

LCD1602 lcd;
PinExpansion expn;
RotaryEncoder knob1(12, 13);
RotaryEncoder knob2(14, 2);
Oled oled(0x3C, 128, 64);
DeviceContainer devices;
WebServer websvr("udomsuk_downstairs_24", "chandpoung");

void setup()
{
    websvr.onConnecting = onWebServerConnecting;
    websvr.onConnected = onWebServerConnected;
    websvr.onClientConnected = onClientConnected;
    websvr.onClientDataRequest = onClientDataRequest;

    knob1.onValueChanged = onKnob1Changed;
    knob2.onValueChanged = onKnob2Changed;

    devices.addDevice(lcd);
    devices.addDevice(expn);
    devices.addDevice(knob1);
    devices.addDevice(knob2);
    devices.addDevice(websvr);
    devices.addDevice(oled);

    Serial.begin(115200);
    devices.setup();
    expn.pcf.write(0, HIGH);
    expn.pcf.setButtonMask(0xFF); // PIN 01 is a button (output pin)

    oled.setYellowText("Connecting");
    oled.getOled().display();
}

void loop()
{
    static unsigned long last = millis();

    devices.loop();
    _updateLCDDisplay();
    _updateOLEDDisplay();

    if (millis() - last > 1000)
    {
        uint8_t current = expn.pcf.read(0);
        expn.pcf.write(0, !current);
        last = millis();
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

void onKnob1Changed(int newval, int oldval)
{
    uint8_t unpressed = expn.pcf.read(EXPN_KNOB_PIN); // for rotary, unpressed = 1, pressed = 0
    flightController.rotateKnob(newval - oldval, unpressed);
}

void onKnob2Changed(int newval, int oldval)
{
}

void _updateLCDDisplay()
{
    static String currentValue = "";
    static String currentTitle = "";

    if (flightData.available() && (currentTitle != flightData.inputTitle() || currentValue != flightData.inputValue()))
    {
        lcd.lcd.clear();
        lcd.lcd.setCursor(0, 0);
        lcd.lcd.print(flightData.inputTitle());

        lcd.lcd.setCursor(0, 1);
        lcd.lcd.print(flightData.inputValue());
        currentTitle = flightData.inputTitle();
        currentValue = flightData.inputValue();
    }
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
