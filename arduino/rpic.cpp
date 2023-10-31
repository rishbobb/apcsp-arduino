#include "rpic.hpp"

// constructor definition, set baudrate
RPIC::RPIC(int baudrate)
{
    (*this).baudrate = baudrate;
}

// setup definition
void RPIC::setup()
{
    // begin serial
    Serial.begin((*this).baudrate);

    // wait for serial
    while (!Serial)
    {
        ;
    }
}

// returns true if new data available recieved from RPI
bool RPIC::available()
{
    return (Serial.available() > 0);
}

// get message from RPI, automatically cast to RPICMessage enum for code readability
RPICMessage RPIC::getMessage()
{
    return static_cast<RPICMessage>(Serial.read());
}