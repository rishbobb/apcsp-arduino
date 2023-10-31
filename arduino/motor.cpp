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
    // if going in positive dir, a HIGH b LOW
    if (speed > 0)
    {
        digitalWrite((*this).a, HIGH);
        digitalWrite((*this).b, LOW);
    }
    // going in negative dir, a LOW b HIGH
    else if (speed < 0)
    {
        digitalWrite((*this).a, LOW);
        digitalWrite((*this).b, HIGH);
    }
    // if not moving, both LOW
    else
    {
        digitalWrite((*this).a, LOW);
        digitalWrite((*this).b, LOW);
    }

    // set speed value in PWM port
    analogWrite((*this).pwm, abs(speed));
}