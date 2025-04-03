#ifndef COCKPIT_HEADER
#define COCKPIT_HEADER

// ATMEGA328P Pinout
// SPI for bootloader: 1 (RESET), 17 (MOSI), 18 (MISO), 19 (SCK)
// SPI for OLED Display: 14 (CS1), 15 (CS2),16 (DC),11 (RES1), 12 (RES2) ,17 (MOSI), 19 (SCK)
// I2C for LCD display: 27 (SDA),28 (SCL)
// USART for connecting ATMEGA328Ps: 2 (RX), 3 (TX)
// DFPlayer mini Audio Serial pins: 5 (TX) and 6 (RX)
// LED shift register: 11 (MR), 12 (ST_CP), 25 (DS), 26 (SH_CP)
// UART communication indicator : 13

// import LCD Display functions
#include "./LCD_Display.h"

// import OLED Display functions
#include "./OLED_display.h"

// import DFPlayer Mini library
#include "./Speaker.h"

// LED indicator 
//Pin connected to ST_CP of 74HC595
#define LATCH_PIN A2
//Pin connected to SH_CP of 74HC595
#define CLOCK_PIN A1
//Pin connected to DS of 74HC595
#define DATA_PIN  A0
// Pin define clear shift register 
#define CLEAR_PIN A3

//Connector Pin
#define CONNECTOR_PIN 4

// NMOS gate pin
#define GATE_PIN 2

// Start button
#define START_PIN 3

/* This function sets up the multiple LEDs to the initial state */
void LED_startup();

/* This function sets up the multiple cockpit devices to the initial state
lcd --- LiquidCrystal_I2C object defined to communicate with the LCD display. Name should be lcd. */
void LCD_startup(LiquidCrystal_I2C lcd);

/* This function sets up the OLED display to the initial state
pitch_display & roll_display --- Adafruit_SSD1306 object used to communicate with the OLED display. */
void OLED_startup(Adafruit_SSD1306 pitch_display, Adafruit_SSD1306 roll_display);

/* This function sets up the DFPlayer Mini to the initial state
folder & track --- integer to specify the folder and track number for the DFPlayer Mini
playBack_time --- integer to specify the playback time in milliseconds */
void Speaker_output(int folder, int track, int playback_time);

/* This functions is used to read the bytes from the UART connection from other MCUs
parameter_array --- An int array of size 4 which stores the values for [score, pitch, roll, device]*/
void get_UART_signal(int parameter_array[4]);

/* This function is used to get the turn dial function 
pitch_display & roll_display --- Adafruit_SSD1306 object used to communicate with the OLED display.
lcd --- LiquidCrystal_I2C object defined to communicate with the LCD display. Name should be lcd.
parameter_array --- An int array of size 4 which stores the values for [score, pitch, roll, device]
time --- interger of the time from when the game began */ 
void display_turn_dial(Adafruit_SSD1306 pitch_display, Adafruit_SSD1306 roll_display, LiquidCrystal_I2C lcd, int parameter_array[4],int time);

/* This function is used to get the move joystick function 
pitch_display & roll_display --- Adafruit_SSD1306 object used to communicate with the OLED display.
lcd --- LiquidCrystal_I2C object defined to communicate with the LCD display. Name should be lcd.
parameter_array --- An int array of size 4 which stores the values for [score, pitch, roll, device]
time --- interger of the time from when the game began 
direction -- character to specify the audio direction 'u' = pull up, 'd' = pull down, 'l' = turn left, 'r' = turn right */ 
void display_move_joystick(char direction, Adafruit_SSD1306 pitch_display, Adafruit_SSD1306 roll_display, LiquidCrystal_I2C lcd, int parameter_array[4],int time);

/* This function is used to get the turn dial function 
pitch_display & roll_display --- Adafruit_SSD1306 object used to communicate with the OLED display.
lcd --- LiquidCrystal_I2C object defined to communicate with the LCD display. Name should be lcd.
parameter_array --- An int array of size 4 which stores the values for [score, pitch, roll, device]
time --- interger of the time from when the game began */ 
void display_press_button(Adafruit_SSD1306 pitch_display, Adafruit_SSD1306 roll_display, LiquidCrystal_I2C lcd, int parameter_array[4],int time);

/* This function is display the game over screen 
pitch_display & roll_display --- Adafruit_SSD1306 object used to communicate with the OLED display.
lcd --- LiquidCrystal_I2C object defined to communicate with the LCD display. Name should be lcd.
parameter_array --- An int array of size 4 which stores the values for [score, pitch, roll, device]
time --- interger of the time from when the game began */ 
void display_game_over(Adafruit_SSD1306 pitch_display, Adafruit_SSD1306 roll_display, LiquidCrystal_I2C lcd, int parameter_array[4],int time);


#endif 