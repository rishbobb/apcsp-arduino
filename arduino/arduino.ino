#include "LiquidCrystal.h"
#include "ArduinoJson.h"

#define BUTTON_PIN 3
#define SPEAKER 4

LiquidCrystal lcd(13, 12, 8, 7, 6, 5);
String colors[] = {"off", "violet", "indigo", "blue", "green", "yellow", "orange", "red"};

int counter = 0;
int ticks = 0;
int asciiDemoVal = 33;

char ASCIIToChar(byte ascii)
{
    return ascii + "\0";
}

void setColor(int red, int green, int blue)
{
    analogWrite(11, red);
    analogWrite(10, green);
    analogWrite(9, blue);
}

void initializeLCDPins()
{
    pinMode(11, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
}

void printLCD(String text, int line = 0)
{
    if (line == 0)
    {
        lcd.clear();
    }
    lcd.setCursor(0, line);
    lcd.print(text);
}

StaticJsonDocument<500> readJSON(String jsonString)
{
    StaticJsonDocument<500> doc;
    DeserializationError error = deserializeJson(doc, jsonString);
    return doc;
}

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

void wirelessWrite(StaticJsonDocument<500> doc)
{
    if (doc["type"] == "w")
    {
        printLCD(doc["line"]);
    }
}

void wirelessSpeaker(StaticJsonDocument<500> doc)
{
    if (doc["type"] == "s")
    {
        if (doc["hz"] == 0)
        {
            noTone(SPEAKER);
        }
        else
        {
            tone(SPEAKER, doc{"hz"});
        }
    }
}

void setup()
{
    lcd.begin(16, 2);
    lcd.clear();

    initializeLCDPins();

    Serial.begin(9600);
    pinMode(BUTTON_PIN, INPUT);
    pinMode(SPEAKER, OUTPUT);

    while (!Serial)
    {
        ; // wait for serial
    }
}

void imrieRequirements(bool print = false)
{
    if (digitalRead(BUTTON_PIN) == LOW)
    {
        setColor(0, 0, 0);
        counter++;
        asciiDemoVal++;

        if (asciiDemoVal > 126)
        {
            asciiDemoVal = 0;
        }
    }

    if (print)
    {
        printLCD(colors[counter] + " " + ASCIIToChar(asciiDemoVal), 1);
    }

    switch (counter)
    {
    case 0:
        setColor(0, 0, 0);
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
        setColor(255, 0, 0);
        break;
    case 8:
        counter = 0;
        break;
    default:
        counter = 0;
        break;
    }
}

void loop()
{
    if (ticks % 50 == 0)
    {
        imrieRequirements();
    }

    String line = getLineFromSerial();
    if (!(line == "null"))
    {
        StaticJsonDocument<500> doc = readJSON(line);
        wirelessWrite(doc);
        wirelessSpeaker(doc);
    }

    ticks++;
    delay(1);
}