#include <Arduino.h>

// Rotary encoder pins
const int pinCLK = 2;
const int pinDT = 3;
const int pinSW = 4;

// State tracking
int lastCLKState = HIGH;
bool buttonPressed = false;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
    pinMode(pinCLK, INPUT);
    pinMode(pinDT, INPUT);
    pinMode(pinSW, INPUT_PULLUP);

    Serial.begin(9600);
    lastCLKState = digitalRead(pinCLK);
}

void loop() {
    // Read rotary encoder state
    int currentCLKState = digitalRead(pinCLK);

    if (currentCLKState != lastCLKState) {
        if (digitalRead(pinDT) != currentCLKState) {
            Serial.print("U");  // Clockwise
        } else {
            Serial.print("D");  // Counter-clockwise
        }
        lastCLKState = currentCLKState;
        delay(1);  // Minor debounce
    }

    // Handle button press with debounce
    if (digitalRead(pinSW) == LOW && !buttonPressed) {
        unsigned long currentTime = millis();
        if (currentTime - lastDebounceTime > debounceDelay) {
            buttonPressed = true;
            Serial.print("M");  // Mute toggle
            lastDebounceTime = currentTime;
        }
    }

    if (digitalRead(pinSW) == HIGH && buttonPressed) {
        buttonPressed = false;
        lastDebounceTime = millis();
    }
}
