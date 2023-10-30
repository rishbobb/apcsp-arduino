#include "bot.hpp"

Bot::Bot(int ain1, int ain2, int pwma, int bin1, int bin2, int pwmb)
{
    leftw = Motor(ain1, ain2, pwma);
    rightw = Motor(bin1, bin2, pwmb);
}

void Bot::setup()
{
    (*this).leftw.setup();
    (*this).rightw.setup();
}

void Bot::move(RPICMessage direction, int speed)
{
    if (direction == (*this).cur)
    {
        (*this).leftw.move(0);
        (*this).rightw.move(0);
        (*this).cur = stopped;
        return;
    }
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
    (*this).cur = direction;
}