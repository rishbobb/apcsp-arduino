#ifndef RPIC_HPP
#define RPIC_HPP

#include <Arduino.h>

enum RPICMessage {
    forward = 48, // 0
    backward = 49, // 1
    left = 50, // 2
    right = 51, // 3
    get_info = 52, // 4
    horn_flip = 53, // 5
    led_front_left_flip = 54, // 6
    led_front_right_flip = 55, // 7
    led_back_left_flip = 56, // 8
    led_back_right_flip = 57, // 9
    stopped = 0 // placeholder val
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