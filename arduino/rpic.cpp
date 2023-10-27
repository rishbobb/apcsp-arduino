#include "rpic.hpp"

RPIC::RPIC(int baudrate)
{
    (*this).baudrate = baudrate;
}

void RPIC::setup()
{
    Serial.begin((*this).baudrate);

    while (!Serial)
    {
        ;
    }
}

bool RPIC::available()
{
    return (Serial.available() > 0);
}

RPICMessage RPIC::getMessage()
{
    return static_cast<RPICMessage>(Serial.read());
}