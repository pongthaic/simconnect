#include "devices_container.h"
#include <malloc.h>

DeviceContainer::DeviceContainer()
{
    this->devices = (Device **)malloc(sizeof(Device) * MAX_DEVICES);
}

void DeviceContainer::addDevice(Device &pDevice)
{
    this->devices[this->devicesCount] = &pDevice;
    this->devicesCount++;
}

int DeviceContainer::getDevicesCount()
{
    return this->devicesCount;
}

void DeviceContainer::setup()
{
    for (int i = 0; i < this->devicesCount; i++)
    {
        this->devices[i]->setup();
    }
}

void DeviceContainer::loop()
{
    for (int i = 0; i < this->devicesCount; i++)
    {
        this->devices[i]->loop();
    }
}