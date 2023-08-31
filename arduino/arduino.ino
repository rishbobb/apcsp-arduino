#include "include/LiquidCrystal.h"

#define BUTTON_PIN 3

LiquidCrystal lcd(13,12,8,7,6,5);

int counter = 0;
int ticks = 0;

void setColor(int red, int green, int blue) {
    analogWrite(11, red);
    analogWrite(10, green);
    analogWrite(9, blue);
}

void initializeLCDPins() {
    pinMode(11, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
}

void printLCD(String text) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(text);
}

void wirelessWrite() {
    if (Serial.available() > 0) {
        printLCD(Serial.readStringUntil("\n"))
    }
}

void setup() {
    lcd.begin(16,2);
    lcd.clear();

    initializeLCDPins();

    Serial.begin(9600);
    pinMode(BUTTON_PIN, INPUT);

    while (!Serial) {
        ; // wait for serial
    }
}

void imrieRequirements() {
    if (digitalRead(BUTTON_PIN) == LOW) {
        setColor(0,0,0);
        counter++;
    }

    // printLCD(counter)

    switch(counter) {
        case 0:
            setColor(0,0,0);
            // printLCD("off")
            break;
        case 1:
            setColor(148, 0, 211);
            break;
        case 2:
            setColor(75, 0, 130);
            break;
        case 3:
            setColor(0, 0, 255);
            break;
        case 4:
            setColor(0, 255, 0);
            break;
        case 5:
            setColor(255, 255, 0);
            break;
        case 6:
            setColor(255, 127, 0);
            break;
        case 7:
            setColor(255, 0 , 0);
            break;
        case 8:
            counter = 0;
            break;
        default:
            counter = 0;
            break;
    }
}

void loop() {
    if (ticks % 20 == 0) {
        imrieRequirements();
    }

    wirelessWrite();
    
    ticks++;
}