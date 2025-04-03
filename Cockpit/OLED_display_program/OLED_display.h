#ifndef OLED_DISPLAY_H
#define OLED_DISPLAY_H

/**************************************************************************
 This is an example for our Monochrome OLEDs based on SSD1306 drivers

 Pick one up today in the adafruit shop!
 ------> http://www.adafruit.com/category/63_98

 This example is for a 128x64 pixel display using SPI to communicate
 4 or 5 pins are required to interface.

 Adafruit invests time and resources providing this open
 source code, please support Adafruit and open-source
 hardware by purchasing products from Adafruit!

 Written by Limor Fried/Ladyada for Adafruit Industries,
 with contributions from the open source community.
 BSD license, check license.txt for more information
 All text above, and the splash screen below must be
 included in any redistribution.
 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// pin number corresponds to the digital pin numbers at https://docs.arduino.cc/retired/hacking/hardware/PinMapping168/
#define OLED_MOSI   11
#define OLED_CLK   13
#define OLED_DC    6
#define OLED_CS    5
#define OLED_RESET 7
#define OLED_CS_ROLL 8
#define OLED_RESET_ROLL 9

// PI is already defined in arduino.h

/* This function displays the pitch indicator without movement
    input:
    display --- Adafruit_SSD1306 struct that specifies the SPI pins used for the OLED display */
void displayPitchIndicator_static(Adafruit_SSD1306 display);

/* This function displays the roll indicator without movement
    input:
    display --- Adafruit_SSD1306 struct that specifies the SPI pins used for the OLED display */
void displayRollIndicator_static(Adafruit_SSD1306 display);

/* This function displays the pitch indicator that changes based on pitch (-30 to 30 degrees)
    input:
    display --- Adafruit_SSD1306 struct that specifies the SPI pins used for the OLED display 
    pitch --- pitch angle given in degrees */
void displayPitchIndicator_transient(Adafruit_SSD1306 display,int pitch);

/* This function displays the roll indicator that changes based on roll (-20 to 20 degrees)
    input:
    display --- Adafruit_SSD1306 struct that specifies the SPI pins used for the OLED display 
    roll --- roll angle given in degrees */
void displayRollIndicator_transient(Adafruit_SSD1306 display,int roll);



#endif