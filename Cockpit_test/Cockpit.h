#ifndef COCKPIT_HEADER
#define COCKPIT_HEADER

// ATMEGA328P Pinout
// SPI for bootloader: 1 (RESET), 17 (MOSI), 18 (MISO), 19 (SCK)
// SPI for OLED Display: 11 (CS),12 (DC),13 (RES),14 (CS),15 (RES),17 (MOSI),19 (SCK)
// I2C for LCD display: 27 (SDA),28 (SCL)
// USART for connecting ATMEGA328Ps: 2 (RX), 3 (TX)
// DFPlayer mini Audio Serial pins: 5 (TX) and 6 (RX)
// LED shift register: 6 (MR), 23 (serial data input), 24 (shift register clock), 25 (storage resiter clock)
// UART communication indicator : 4

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
#define CLEAR_PIN 4

//Connector Pin
#define CONNECTOR_PIN 2

/* This function sets up the multiple cockpit devices to the initial state
lcd --- LiquidCrystal_I2C object defined to communicate with the LCD display. Name should be lcd. 
pitch_display & roll_display --- Adafruit_SSD1306 object used to communicate with the OLED display.
mySoftwareSerial -- SoftwareSerial object to use digital pins 3 and 4 as UART serial ports.
myDFPlayer --- DFRobotDFPlayerMIni object to communicate with the DFPlayer mini. */
void cockpit_startup(LiquidCrystal_I2C lcd,Adafruit_SSD1306 pitch_display, Adafruit_SSD1306 roll_display, SoftwareSerial mySoftwareSerial,DFRobotDFPlayerMini myDFPlayer);


#endif 