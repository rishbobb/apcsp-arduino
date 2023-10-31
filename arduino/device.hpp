#ifndef DEVICE_HPP
#define DEVICE_HPP

#include <Arduino.h>

// class for basic single pin devices
class Device
{
public:
    // instance variables
    int port, state;

    // constructor decleration (takes port)
    Device(int port);

    // other function declerations
    void setup();

    void trigger(int val);

    int getState();

    void flip();

    int isTriggered();

    float getAnalog();
};

#endif