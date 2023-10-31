#ifndef ULTRASONIC_HPP
#define ULTRASONIC_HPP

#include <Arduino.h>

class Ultrasonic
{
public:
    // instance vars
    int echo, trig;

    // constructor decleration
    Ultrasonic(int echo, int trig);

    // function declerations
    void setup();

    float getDistance();
};

#endif