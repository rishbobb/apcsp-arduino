#include "motor.hpp"

// Motor constructor definition
Motor::Motor(int a, int b, int pwm)
{
    (*this).a = a;
    (*this).b = b;
    (*this).pwm = pwm;
}

// dummy constructor
Motor::Motor() {
    (*this).a = 0;
    (*this).b = 0;
    (*this).pwm = 0;
}

// Motor setup func definition
void Motor::setup()
{
    pinMode((*this).a, OUTPUT);
    pinMode((*this).b, OUTPUT);
    pinMode((*this).pwm, OUTPUT);
}

// Motor move function definition
void Motor::move(int speed)
{
    if (speed > 0)
    {
        digitalWrite((*this).a, HIGH);
        digitalWrite((*this).b, LOW);
    }
    else if (speed < 0)
    {
        digitalWrite((*this).a, LOW);
        digitalWrite((*this).b, HIGH);
    }
    else
    {
        digitalWrite((*this).a, LOW);
        digitalWrite((*this).b, LOW);
    }

    analogWrite((*this).pwm, abs(speed));
}