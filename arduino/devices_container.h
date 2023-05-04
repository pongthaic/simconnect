#ifndef __DEVICE_CONTAINER_H
#define __DEVICE_CONTAINER_H

#include "devices/device.h"

#define MAX_DEVICES 10

class DeviceContainer
{
public:
    DeviceContainer();
    void addDevice(Device &device);
    int getDevicesCount();
    void setup();
    void loop();

private:
    int devicesCount = 0;
    Device **devices = 0;
};

#endif