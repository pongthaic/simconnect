#ifndef __FLIGHT_CONTROLLER_H
#define __FLIGHT_CONTROLLER_H

/**
 * This class monitors and receives user inputs
 * and process with according function.
 */
class FlightController
{
public:
    FlightController();

    void turnSwitch(int switchNo, bool on);
    void rotateKnob(int detents, int pushState = 0);
    void rotateTrim(int detents);
    void pressButton(int buttonNo);
};

// Singleton controller.
FlightController flightController;

#include "flight_controller.cpp"
#endif