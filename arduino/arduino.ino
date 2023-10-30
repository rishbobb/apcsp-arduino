#include "bot.hpp"
#include "ultrasonic.hpp"
#include "device.hpp"
#include "rpic.hpp"

// - PORT DEFINITIONS -
// Ultrasonic
#define ECHO_F 50
#define TRIG_F 52
#define ECHO_B 51
#define TRIG_B 53
//Sound
#define SOUND 46
// Motor Controller
#define AIN1 8
#define AIN2 9
#define PWMA 5
#define BIN1 11
#define BIN2 12
#define PWMB 6
// LED     
#define LED_FRONT_LEFT 38
#define LED_FRONT_RIGHT 39
#define LED_BACK_LEFT 40
#define LED_BACK_RIGHT 41
// Horn
#define HORN 43

Bot bot(AIN1, AIN2, PWMA, BIN1, BIN2, PWMB);
Ultrasonic front(ECHO_F, TRIG_F);
Ultrasonic back(ECHO_B, TRIG_B);
Device horn(HORN);
RPIC rpi(2000000);
Device front_left_led(LED_FRONT_LEFT);
Device front_right_led(LED_FRONT_RIGHT);
Device back_left_led(LED_BACK_LEFT);
Device back_right_led(LED_BACK_RIGHT);

void setup()
{
    // Ultrasonic
    front.setup();
    back.setup();

    // Motor Controller
    bot.setup();

    // LED
    front_left_led.setup();
    front_right_led.setup();
    back_left_led.setup();
    back_right_led.setup();

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
        RPICMessage message = rpi.getMessage();
        Serial.println(message);
        bot.move(message, 255);
        switch (message) {
            case horn_on:
                horn.trigger(HIGH);
                break;
            case horn_off:
                horn.trigger(LOW);
                break;
            case led_front_left_on:
                front_left_led.trigger(HIGH);
                break;
            case led_front_left_off:
                front_left_led.trigger(LOW);
                break;
            case led_front_right_on:
                front_right_led.trigger(HIGH);
                break;
            case led_front_right_off:
                front_right_led.trigger(LOW);
                break;
            case led_back_left_on:
                back_left_led.trigger(HIGH);
                break;
            case led_back_left_off:
                back_left_led.trigger(LOW);
                break;
            case led_back_right_on:
                back_right_led.trigger(HIGH);
                break;
            case led_back_right_off:
                back_right_led.trigger(LOW);
                break;
            case get_alarm:
                break;
            case get_dist_front:
                break;
            case get_dist_back:
                break;
        }
    }
}