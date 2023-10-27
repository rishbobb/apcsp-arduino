#ifndef BOT_HPP
#define BOT_HPP

#include <Arduino.h>
#include "motor.hpp"
#include "rpic.hpp"

class Bot
{
public:
    // decleration of instance variables
    Motor leftw, rightw;

    // constructor decleration
    Bot(int ain1, int ain2, int pwma, int bin1, int bin2, int pwmb);

    // setup func decleration
    void setup();

    // move func decleration
    void move(RPICMessage direction, int speed);
};

#endif