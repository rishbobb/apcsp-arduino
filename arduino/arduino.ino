#include "LiquidCrystal.h"

#define BUTTON_PIN 3

LiquidCrystal lcd(13,12,8,7,6,5);
String colors[] = {"off", "violet", "indigo", "blue", "green", "yellow", "orange", "red"};

int counter = 0;
int ticks = 0;
int asciiDemoVal = 33;

char ASCIIToChar(byte ascii) {
  return ascii + "\0";
}

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

void printLCD(String text, int line = 0) {
    if (line == 0) {
        lcd.clear();
    }
    lcd.setCursor(line,0);
    lcd.print(text);
}

void wirelessWrite() {
    if (Serial.available() > 0) {
        String line = Serial.readStringUntil("\n");
        line.remove(line.length()-1);
        printLCD(line);
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
        asciiDemoVal++;

        if (asciiDemoVal > 126) {
            asciiDemoVal = 0;
        }
    } 

    printLCD(colors[counter] + " " + ASCIIToChar(asciiDemoVal), 1);

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
    if (ticks % 50 == 0) {
        imrieRequirements();
    }

    wirelessWrite();
    
    ticks++;
    delay(1);
}