// - HEADER FILES INCLUDES -
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
// Motor Controller
#define AIN1 8
#define AIN2 9
#define PWMA 5
#define BIN1 11
#define BIN2 12
#define PWMB 6
// LEDs
#define LED_FRONT_LEFT 38
#define LED_FRONT_RIGHT 39
#define LED_BACK_LEFT 40
#define LED_BACK_RIGHT 41
// Horn
#define HORN 43
// Sound detector
#define SOUND A15

// create bot object from motor controller ports
Bot bot(AIN1, AIN2, PWMA, BIN1, BIN2, PWMB);

// create two ultrasonic sensor objects
Ultrasonic front(ECHO_F, TRIG_F);
Ultrasonic back(ECHO_B, TRIG_B);

// create horn and sound detector
Device horn(HORN);
Device sound_detector(SOUND);

// create a RPI (Raspberry Pi) Communication object
RPIC rpi(2000000);

// create four LEDs
Device front_left_led(LED_FRONT_LEFT);
Device front_right_led(LED_FRONT_RIGHT);
Device back_left_led(LED_BACK_LEFT);
Device back_right_led(LED_BACK_RIGHT);

// setup func
void setup()
{
    // Ultrasonic
    front.setup();
    back.setup();

    // Motor Controller
    bot.setup();

    // LEDs
    front_left_led.setup();
    front_right_led.setup();
    back_left_led.setup();
    back_right_led.setup();

    // Horn
    horn.setup();

    // rpic connection
    Serial.begin(2000000);

    // wait for serial
    while (!Serial)
    {
        ;
    }
}

// car alarm variables
int alarm_timeout = 0;
bool alarm = false;
int user_horn = LOW;
void loop()
{
    // get analog sound detected
    float sound_detected = sound_detector.getAnalog();

    // if the sound is 600 or higher, and the UI has not communicated for at least 2000 iterations, set the alarm
    if (sound_detected >= 600 && alarm_timeout >= 2000)
    {
        alarm = true;
    }

    // run only if RPI has sent data over serial
    if (rpi.available())
    {
        // if the UI communicates, the alarm must be turned off
        alarm_timeout = 0;
        alarm = false;

        // get the message (automatically cast to an enum)
        RPICMessage message = rpi.getMessage();

        // move the bot using the message (if the message was a command for the drivetrain)
        bot.move(message, 255);

        // if the command was something else, do that in this switch statement
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
            // send info over serial
            Serial.println(front.getDistance());
            Serial.println(back.getDistance());
            Serial.println(sound_detected);
            break;
        }
    }
    else
    {
        // iterate alarm timeout if UI has not communicated
        alarm_timeout++;
    }

    // if alarm is set, turn on alarm
    if (alarm && alarm_timeout >= 2000)
    {
        horn.trigger(HIGH);
    }
    else
    {
        // if the horn is not in sync with the UI, make it in sync
        if (user_horn != horn.getState())
        {
            horn.trigger(user_horn);
        }
    }
}