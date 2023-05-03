#ifndef __DEVICE_H

#define __DEVICE_H

class Device
{
    virtual void setup() = 0;
    virtual void loop() = 0;
};

#endif