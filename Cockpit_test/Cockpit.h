#ifndef COCKPIT_HEADER
#define COCKPIT_HEADER

// import LCD Display functions
#include "./LCD_Display.h"

// import OLED Display functions
#include "./OLED_display.h"

// import DFPlayer Mini library
#include "./Speaker.h"

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

// LED indicator 
//Pin connected to ST_CP of 74HC595
#define LATCH_PIN A2
//Pin connected to SH_CP of 74HC595
#define CLOCK_PIN A1
//Pin connected to DS of 74HC595
#define DATA_PIN  A0
// Pin define clear shift register 
#define CLEAR_PIN A3

// NMOS gate pin
#define GATE_PIN 2

// Start button
#define START_PIN 3

// Game Line Pin
#define GAMELINE_PIN 4

/* This function sets up the multiple LEDs to the initial state */
void LED_startup();

/* This function sets up the multiple cockpit devices to the initial state  */ 
void LCD_startup(LiquidCrystal_I2C &lcd);

/* This function sets up the OLED display to the initial state */
void OLED_startup(Adafruit_SSD1306 &pitch_display, Adafruit_SSD1306 &roll_display);
void OLED_end(Adafruit_SSD1306 &pitch_display, Adafruit_SSD1306 &roll_display);

/* This function sets up the DFPlayer Mini to the initial state */
void Speaker_output(int folder, int track, int playback_time);

/* This function is used to read the bytes from the UART connection from other MCUs */
void get_UART_signal(Command& cmd, bool& newData);

/* This function checks whether the start button is pressed and sends a signal high to the game line pin */
void notify_start_button_pressed();

/* display for debugging */
void debug(const LiquidCrystal_I2C& lcd, const Command& cmd);


#endif 