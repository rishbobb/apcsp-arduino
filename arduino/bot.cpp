#include "bot.hpp"

// constructor definition
Bot::Bot(int ain1, int ain2, int pwma, int bin1, int bin2, int pwmb)
{
    // initialize motors
    leftw = Motor(ain1, ain2, pwma);
    rightw = Motor(bin1, bin2, pwmb);
}

// setup function definition
void Bot::setup()
{
    // run setup functions for each individual motor
    (*this).leftw.setup();
    (*this).rightw.setup();
}

// move function definition (takes RPICMessage enum and speed 0-255)
void Bot::move(RPICMessage direction, int speed)
{
    // if same direction, stop the car
    if (direction == (*this).cur)
    {
        (*this).leftw.move(0);
        (*this).rightw.move(0);
        (*this).cur = stopped;
        return;
    }

    // if new direction, switch
    switch (direction)
    {
    case forward:
        (*this).leftw.move(speed);
        (*this).rightw.move(speed);
        break;
    case backward:
        (*this).leftw.move(-speed);
        (*this).rightw.move(-speed);
        break;
    case left:
        (*this).leftw.move(-speed);
        (*this).rightw.move(speed);
        break;
    case right:
        (*this).leftw.move(speed);
        (*this).rightw.move(-speed);
        break;
    }

    // set current direction to new direction
    (*this).cur = direction;
}