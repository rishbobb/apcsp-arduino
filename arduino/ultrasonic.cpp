#include "ultrasonic.hpp"

// ultrasonic constructor definition
Ultrasonic::Ultrasonic(int echo, int trig)
{
    (*this).echo = echo;
    (*this).trig = trig;
}

// setup pins
void Ultrasonic::setup()
{
    pinMode((*this).echo, INPUT);
    pinMode((*this).trig, OUTPUT);
}

// get distance function using the formula
float Ultrasonic::getDistance()
{
    digitalWrite((*this).trig, LOW);
    delayMicroseconds(2);
    digitalWrite((*this).trig, HIGH);
    delayMicroseconds(10);
    digitalWrite((*this).trig, LOW);
    float duration = pulseIn((*this).echo, HIGH);
    float distance = duration * 0.0344 / 2;
    return distance;
}