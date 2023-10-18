// - PORT DEFINITIONS -
// Ultrasonic
#define TRIG 3
#define ECHO 2
// Motor Controller
#define AIN1 8
#define AIN2 9
#define PWMA 5
#define BIN1 11
#define BIN2 12
#define PWMB 6
// LED
#define LED 13

String getLineFromSerial()
{
    if (Serial.available() > 0)
    {
        String line = Serial.readStringUntil("\n");
        line.remove(line.length() - 1);
        return line;
    }
    else
    {
        return "null";
    }
}

// Motor class def (to make later code better with OOP)
class Motor
{
public:
    // port vals
    int a, b, pwm;

    // constructor
    Motor(int a, int b, int pwm)
    {
        (*this).a = a;
        (*this).b = b;
        (*this).pwm = pwm;
    }

    // move function
    void move(int speed)
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
};

// get distance from ultrasonic
float getDistance()
{
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    float duration = pulseIn(ECHO, HIGH);
    float distance = duration * 0.034 / 2;
    return distance;
}

// left and right motors (using class i made)
Motor left(AIN1, AIN2, PWMA);
Motor right(BIN1, BIN2, PWMB);

void setup()
{
    // Ultrasonic
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

    // Motor Controller
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    pinMode(PWMB, OUTPUT);

    // LED
    pinMode(LED, OUTPUT);

    // Serial
    Serial.begin(9600);

    while (!Serial)
    {
        ; // wait for serial
    }
}

void loop()
{
    // get distance in float val
    //   float distance = getDistance();

    // if there is an object near
    //   if (distance < 35) {
    //     // turn on backup LED
    //     digitalWrite(LED, HIGH);
    //     // TURN cause backing up just puts the bot into a loop
    //     right.move(0);
    //     left.move(-250);
    //     delay(1000);
    //   } else {
    //     // Normally keep LED off
    //     digitalWrite(LED, LOW);
    //     // move forward (vals are different because of small issue with wheels turning at diff speeds)
    //     right.move(250);
    //     left.move(250);
    //     delay(1000);
    //   }
    String line = getLineFromSerial();
    if (!(line == "null")) {
        if (line == "forward")
        {
            left.move(150);
            right.move(150);
        }
        else if (line == "backward")
        {
            left.move(-150);
            right.move(-150);
        }
        else if (line == "left")
        {
            left.move(-150);
            right.move(150);
        }
        else if (line == "right")
        {
            left.move(150);
            right.move(-150);
        }
        else if (line == "stop") {
            left.move(0);
            right.move(0);
        }
    }
}