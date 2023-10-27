#include "bot.hpp"
#include "ultrasonic.hpp"
#include "device.hpp"
#include "rpic.hpp"

// - PORT DEFINITIONS -
// Ultrasonic
#define ECHO 50
#define TRIG 52
// Motor Controller
#define AIN1 8
#define AIN2 9
#define PWMA 5
#define BIN1 11
#define BIN2 12
#define PWMB 6
// LED
#define LED 13
// Horn
#define HORN 43

Bot bot(AIN1, AIN2, PWMA, BIN1, BIN2, PWMB);
Ultrasonic front(ECHO, TRIG);
Device led(LED);
Device horn(HORN);
RPIC rpi(2000000);

void setup()
{
    // Ultrasonic
    front.setup();

    // Motor Controller
    bot.setup();

    // LED
    led.setup();

    // Horn
    horn.setup();

    // rpic connection
    Serial.begin(2000000);

    while (!Serial)
    {
        ;
    }
}

void loop()
{
    if (rpi.available())
    {
        led.trigger(HIGH);
        RPICMessage message = rpi.getMessage();
        bot.move(message, 255);
        if (message == horn_on)
        {
            horn.trigger(HIGH);
        }
        else if (message == horn_off)
        {
            horn.trigger(LOW);
        }
    }
}