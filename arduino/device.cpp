#include "device.hpp"

// constructor sets port and initial state
Device::Device(int port)
{
    (*this).port = port;
    (*this).state = LOW;
}

// setup the pin
void Device::setup()
{
    pinMode((*this).port, OUTPUT);
}

// set state to HIGH or LOW (digital)
void Device::trigger(int val)
{
    (*this).state = val;
    digitalWrite((*this).port, val);
}

// get state HIGH or LOW
int Device::getState()
{
    return (*this).state;
}

// set to opposite state as current state
void Device::flip()
{
    if ((*this).state == LOW)
    {
        (*this).trigger(HIGH);
    }
    else
    {
        (*this).trigger(LOW);
    }
}

// check if digitally triggered (for input)
int Device::isTriggered()
{
    return digitalRead((*this).port);
}

// get analog value (for analog devices like sound detector)
float Device::getAnalog()
{
    return analogRead((*this).port);
}