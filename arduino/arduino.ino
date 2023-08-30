#include "LiquidCrystal.h"

#define BUTTON_PIN 3

LiquidCrystal lcd(13,12,8,7,6,5);

int counter = 0;

void setup() {
    lcd.begin(16,2);
    lcd.clear();

    pinMode(11, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(9, OUTPUT);
    Serial.begin(9600);
    pinMode(BUTTON_PIN, INPUT);
}

void loop() {
    lcd.setCursor(0,0);
    lcd.print(counter);
    Serial.println(counter);
    int buttonState;
    buttonState = digitalRead(BUTTON_PIN);
    Serial.println(buttonState);
    if (buttonState == LOW) {
        counter++;
        delay(200);
        lcd.clear();
    }

    if (counter == 0) {
        RGBcolor(0,0,0);
        lcd.setCursor(0,0);
        lcd.clear();
        lcd.print("Off");
    } else if (counter == 1) {
        RGBcolor(235,52,195);
    } else if (counter == 2) {
        RGBcolor(27, 165, 207);
    } else if (counter == 3){
        RGBcolor (150, 75, 29); I
    } else if(counter == 4){
        RGBcolor (122, 29, 150);
    } else if(counter == 5){
        RGBcolor (180, 85, 17);
    } else if(counter == 6){
        counter = 0;
    } else {
        counter = 0;
    }
}

void RGBcolor(int red, int green, int blue) {
    analogWrite(11, red);
    analogWrite(10, green);
    analogWrite(9, blue)
}