#ifndef ULTRASONIC_HPP
#define ULTRASONIC_HPP

#include <Arduino.h>

class Ultrasonic {
    public:
        int echo, trig;

        Ultrasonic(int echo, int trig);

        void setup();

        float getDistance();
};

#endif