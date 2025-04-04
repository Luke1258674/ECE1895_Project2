
#include "./User_input.h"

void setup_GPIOpins(const int ledPins[], const int buttonPins[], bool ledStates[], const int ledControlPins[]){
    // Setup Joystick Pins
    pinMode(JOYSTICK_VRX, INPUT); // X-axis
    pinMode(JOYSTICK_VRY, INPUT); // Y-axis
    pinMode(JOYSTICK_SW, INPUT_PULLUP); // Button input with internal pull-up resistor

    // potentiometer
    pinMode(POTENTIOMETER_PIN, INPUT); // Potentiometer 
    
    // Setup LED Output Pins
    for (int i = 0; i < 2; i++) {
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW); // Start with LEDs off
    }

    // Setup Button Pins
    for (int i = 0; i < 2; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP); // Use internal pull-up resistor
    }

    // Setup Potentiometer LED Pins
    for (int i = 0; i < 4; i++) {
        pinMode(ledControlPins[i], OUTPUT); // Set the LED pins as output
        digitalWrite(ledControlPins[i], LOW); // Start with LEDs off
    }

    // Setup UART connector pin 
    pinMode(CONNECTOR_PIN,OUTPUT);
    digitalWrite(CONNECTOR_PIN,HIGH);

}