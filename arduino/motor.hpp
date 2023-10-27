#ifndef MOTOR_HPP
#define MOTOR_HPP

#include <Arduino.h>

class Motor
{
public:
    // port val decleration
    int a, b, pwm;

    // constrctor decleration
    Motor(int a, int b, int pwm);

    // dummy constructor
    Motor();

    // setup func decleration
    void setup();

    // move function decleration
    void move(int speed);
};

#endif