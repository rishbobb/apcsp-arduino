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
    horn_off = 54,
    get_sound = 97,
    get_dist_front = 98,
    get_dist_back = 99,
    led_front_left_on = 100,
    led_front_left_off = 101,
    led_front_right_on = 102,
    led_front_right_off = 103,
    led_back_left_on = 104,
    led_back_left_off = 105,
    led_back_right_on = 106,
    led_back_right_off = 107,
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