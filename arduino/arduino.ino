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
        Serial.println(line);
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
    Serial.begin(1000000);

    while (!Serial)
    {
        ; // wait for serial
    }
}

void loop()
{
    String line = getLineFromSerial();
    if (!(line == "null")) {
        digitalWrite(LED, HIGH);
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
    } else {
        digitalWrite(LED, LOW);
    }
}