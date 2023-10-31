#include "bot.hpp"
#include "ultrasonic.hpp"
#include "device.hpp"
#include "rpic.hpp"

// - PORT DEFINITIONS -
// Ultrasonic
#define ECHO_F 2
#define TRIG_F 7
#define ECHO_B 4
#define TRIG_B 3
// Sound
#define SOUND A15
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
Device sound_detector(SOUND);
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

int alarm_timeout = 0;
bool alarm = false;
int user_horn = LOW;
void loop()
{
    float sound_detected = sound_detector.getAnalog();

    if (sound_detected >= 600 && alarm_timeout >= 1000)
    {
        alarm = true;
    }

    if (rpi.available())
    {
        alarm_timeout = 0;
        RPICMessage message = rpi.getMessage();
        bot.move(message, 255);
        switch (message)
        {
        case horn_flip:
            horn.flip();
            user_horn = !user_horn;
            break;
        case led_front_left_flip:
            front_left_led.flip();
            break;
        case led_front_right_flip:
            front_right_led.flip();
            break;
        case led_back_left_flip:
            back_left_led.flip();
            break;
        case led_back_right_flip:
            back_right_led.flip();
            break;
        case get_info:
            Serial.println(front.getDistance());
            Serial.println(back.getDistance());
            Serial.println(sound_detected);
            break;
        }
    }
    else
    {
        alarm_timeout++;
    }

    if (alarm && alarm_timeout >= 1000)
    {
        horn.trigger(HIGH);
    }
    else
    {
        if (user_horn != horn.getState())
        {
            horn.trigger(user_horn);
        }
    }
}