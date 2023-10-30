#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <Arduino.h>

class Device
{
public:
    int port, state;

    Device(int port);

    void setup();

    void trigger(int val);

    int getState();

    void flip();

    int isTriggered();

    float getAnalog();
};

#endif