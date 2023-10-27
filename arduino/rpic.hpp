#ifndef RPIC_HPP
#define RPIC_HPP

#include <Arduino.h>

enum RPICMessage {
    forward = 48,
    backward = 49,
    left = 50,
    right = 51,
    stop = 52,
    horn_on = 53,
    horn_off = 54
};

class RPIC {
    public:
        int baudrate;

        RPIC(int baudrate);

        void setup();

        bool available();

        RPICMessage getMessage();
};

#endif