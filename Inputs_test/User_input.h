#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <Arduino.h>
#include <Wire.h>

#define JOYSTICK_VRX A0
#define JOYSTICK_VRY A1
#define JOYSTICK_SW 2
#define POTENTIOMETER_PIN A2
#define GAMELINE_PIN A3

// struct to store yaw, roll, pitch, score, and device used
struct Command{
    //Plane information
    int8_t yaw;
    int8_t roll;
    int8_t pitch;

    //Display info
    uint8_t score;
    uint8_t device_used;
};

/* function to set up the pin mode for all I/Os */
void setup_GPIOpins(const int ledPins[], const int buttonPins[], bool ledStates[], const int ledControlPins[]);

// package data into string to send through UART
void updateDataToSend(unsigned long& prevUpdateTime,unsigned long updateInterval,bool& newTxData); 

// transmit data 
void transmitData(const Command& cmd, bool& newTxData);

// read from potentiometer under turn left action
void turn_left_action(bool& user_action, const int ledControlPins[],int& currentrotory, int& currentY, bool& user_timeout,const int buttonPins[], int& ledsOn);

// read from potentiometer under turn right action
void turn_right_action(bool& user_action, const int ledControlPins[],int& currentrotory, int& currentY, bool& user_timeout,const int buttonPins[], int& ledsOn);

// read joystick during climb action and update user_action flag
void ascend_action(bool& user_action, int& currentrotory, int& currentY, bool& user_timeout,const int buttonPins[], int& ledsOn);

// read joystick during climb action and update user_action flag
void descend_action(bool& user_action, int& currentrotory, int& currentY, bool& user_timeout,const int buttonPins[], int& ledsOn);

// read button during press button action and update user_action flag
void press_button_action(bool& user_action, const int ledPins[], bool ledStates[],const int buttonPins[],int& currentrotory, int& currentY, bool& user_timeout, int& ledsOn);


#endif 

