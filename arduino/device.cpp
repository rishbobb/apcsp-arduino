#include "device.hpp"

Device::Device(int port)
{
    (*this).port = port;
    (*this).state = LOW;
}

void Device::setup()
{
    pinMode((*this).port, OUTPUT);
}

void Device::trigger(int val)
{
    (*this).state = val;
    digitalWrite((*this).port, val);
}

int Device::getState()
{
    return (*this).state;
}

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