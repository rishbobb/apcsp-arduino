#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <Arduino.h>

class Device
{
public:
    int port;

    Device(int port);

    void setup();

    void trigger(int val);
};

#endif