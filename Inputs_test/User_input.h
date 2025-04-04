#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <Arduino.h>

#define JOYSTICK_VRX A0
#define JOYSTICK_VRY A1
#define JOYSTICK_SW 2
#define POTENTIOMETER_PIN A2



// UART Connector pin 
#define CONNECTOR_PIN A3 

/* function to set up the pin mode for all I/Os */
void setup_GPIOpins(const int ledPins[], const int buttonPins[], bool ledStates[], const int ledControlPins[]);

#endif 