#include "ultrasonic.hpp"

Ultrasonic::Ultrasonic(int echo, int trig)
{
    (*this).echo = echo;
    (*this).trig = trig;
}

void Ultrasonic::setup()
{
    pinMode((*this).echo, INPUT);
    pinMode((*this).trig, OUTPUT);
}

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