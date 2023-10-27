#include "device.hpp"

Device::Device(int port)
{
    (*this).port = port;
}

void Device::setup()
{
    pinMode((*this).port, OUTPUT);
}

void Device::trigger(int val)
{
    digitalWrite((*this).port, val);
}