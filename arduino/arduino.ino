/**
 * ARCHITECTURE
 * ============
 *
 *                  FlightDataPresenter <--------------+
 *                           |                         |
 *                           v                         |
 * [user inputs] ===> FlightController ------> ClientInteractor <------- ClientProcessor <=== TCP Client
 *
 *
 */
#include "devices/device.h"
#include "devices/lcd1602.h"
#include "devices/pin_expansion.h"
#include "devices/rotary.h"
#include "devices/tcp_server.h"
#include "devices/oled.h"
#include "devices/flight_data_presenter.h"
#include "devices_container.h"

#include "controller/client_processor.h"
#include "controller/flight_controller.h"
#include "controller/flight_data.h"

#include <stdlib.h>
#include <Arduino.h>

#define EXPN_KNOB_PIN 3

LCD1602 lcd;
PinExpansion expn;
RotaryEncoder knob1(15, 13);
RotaryEncoder knob2(0, 2);
Oled oled(0x3C, 128, 64);
DeviceContainer devices;
TCPServer server("udomsuk_downstairs_24", "chandpoung");
FlightDataPresenter presenter(lcd, expn, oled, flightData);

void setup()
{
    server.onConnecting = onWebServerConnecting;
    server.onConnected = onWebServerConnected;
    server.onClientConnected = onClientConnected;
    server.onReceived = onClientDataReceived;

    knob1.onValueChanged = onKnob1Changed;
    knob2.onValueChanged = onKnob2Changed;

    expn.setInputListener(7, onUpdatedPinState);
    expn.setInputListener(1, onNextInput);
    expn.setInputListener(2, onNextInput);

    devices.addDevice(lcd);
    devices.addDevice(expn);
    devices.addDevice(knob1);
    devices.addDevice(knob2);
    devices.addDevice(server);
    devices.addDevice(oled);
    devices.addDevice(presenter);

    Serial.begin(9600);
    devices.setup();
    expn.pcf.write(0, HIGH);
    expn.pcf.setButtonMask(0xFF); // PIN 01 is a button (output pin)

    oled.setYellowText("Connecting");
    oled.getOled().display();
}

void loop()
{
    devices.loop();
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
    Serial.println("rotated");
    flightController.rotateKnob(newval - oldval, unpressed);
}

void onKnob2Changed(int newval, int oldval)
{
}

void onUpdatedPinState(enum PinState state)
{
    if (state == PIN_RISING)
    {
        flightController.pressButton(7);
    }
}

void onNextInput(enum PinState state)
{
    Serial.printf("Next input, %d\n", state);
    if (state == PIN_RISING)
    {
        flightController.pressButton(1);
    }
}
