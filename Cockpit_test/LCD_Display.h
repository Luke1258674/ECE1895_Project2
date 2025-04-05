#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

// Include the library to communicate with the I2C chip on the 16X2 LCD display
// Pins 27 and 28 must be connected to SDA and SCL for this library to work on atmega328P
#include <LiquidCrystal_I2C.h>


/* This function displays the score and time of the current session of the game.
The code will show time in XX:XX format (Minutes:Seconds). 
Input arguments:
lcd --- LiquidCrystal_I2C object defined in setup(). Name should be lcd. 
score --- Integer with value in range 1 - 99. 
time --- Integer with value in range 0 - 99min*60seconds. Time should be sent as seconds. */
void showScoreAndTime(LiquidCrystal_I2C &lcd, int score, int time);

/* This function displays the word "Press Start to Take Off"
Input argument:
lcd --- LiquidCrystal_I2C object defined in setup(). Name should be lcd. 
*/
void showStartMenu(LiquidCrystal_I2C &lcd);

/* This function displays the word "Game Over" and displays the current score and time
Input argument:
lcd --- LiquidCrystal_I2C object defined in setup(). Name should be lcd. 
score --- Global variable. Integer with value in range 1 - 99. 
time ---  Global variable. Integer with value in range 0 - 99min*60seconds. Time should be sent as seconds. */
void showGameOver(LiquidCrystal_I2C &lcd, int score, int time);


#endif