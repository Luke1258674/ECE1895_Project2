
// Connect hearer files
#include "./User_input.h"
#include <Wire.h>
#include <Arduino.h>

/* Define pins */
// LED output pins
const int ledPins[] = {3, 4}; 

// Button input pins
const int buttonPins[] = {7, 8}; 

// LED toggle states
bool ledStates[2] = {false, false}; 

// Potentiometer and 4 LEDs
const int ledControlPins[] = {5, 6, 9, 10}; // 4 LEDs for potentiometer control
int ledsOn = 0;  // Variable to control how many LEDs are lit

void setup() {
    // initialize I/Os
    setup_GPIOpins(ledPins,buttonPins,ledStates,ledControlPins);
}

void loop() {
  // wait for start button to be pressed

    // --- Joystick Reading (your original code) ---
    int xRaw = analogRead(A0); // Read X-axis
    int yRaw = analogRead(A1); // Read Y-axis

    // Map the values from 0-1023 to -90 to 90
    int xMapped = map(xRaw, 0, 1023, -90, 90);
    int yMapped = map(yRaw, 0, 1023, -90, 90);

    /*
    // Map the joystick value to the number of LEDs to turn on (0-4 range)
    if (xMapped<-50){
      ledsOn=0;
    }else if (xMapped<0){
      ledsOn=1;
    }else if (xMapped<30){
      ledsOn=2;
    }else if (xMapped<60){
      ledsOn=3;
    }else{
      ledsOn=4;
    }
    */

    // Read the Joystick button state (LOW means pressed)
    bool buttonPressed = (digitalRead(2) == LOW);

    // --- Button 1 Reading ---
    if (digitalRead(buttonPins[0]) == LOW) { // Button 1 pressed (LOW state)
      digitalWrite(ledPins[0],HIGH);
      delay(100);
      digitalWrite(ledPins[0],LOW);
    }

    // --- Button 2 Reading ---
    if (digitalRead(buttonPins[1]) == LOW) { // Button 2 pressed (LOW state)
        
        if (digitalRead(buttonPins[1]) == LOW) { // Confirm still pressed
            ledStates[1] = !ledStates[1]; // Toggle LED 2
            digitalWrite(ledPins[1], ledStates[1] ? HIGH : LOW);
        }
        while (digitalRead(buttonPins[1]) == LOW);
    }


    // --- Potentiometer Reading ---
    int potValue = analogRead(A2); // Read the potentiometer value (0 to 1023)

    // Map the potentiometer value to the number of LEDs to turn on (0-4 range)
    if (potValue<=50){
      ledsOn=0;
    }else if (potValue>50&&potValue<260){
      ledsOn=1;
    }else if (potValue>=260&&potValue<512){
      ledsOn=2;
    }else if (potValue>=512&&potValue<760){
      ledsOn=3;
    }else{
      ledsOn=4;
    }
    // Control the potentiometer-controlled LEDs based on the potentiometer value
        for (int i = 0; i < ledsOn; i++){
      digitalWrite(ledControlPins[i],HIGH);
    }

    for (int i = 4; i > ledsOn; i--){
      digitalWrite(ledControlPins[i],LOW);
    }

    delay(100);
    */
}
