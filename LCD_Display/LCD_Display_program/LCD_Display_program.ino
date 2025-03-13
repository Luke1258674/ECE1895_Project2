// Luke Rajakovich
// Ryan Lopez
// Calvin Fetzek

// import LCD Display functions
#include "./LCD_Display.h"

// Step 1. Install the following library from Arduino Library Manager
// LiquidCrystal I2C by Frank de Brabander 

// Step 2. Connect the following pins on the LCD display to the AtMega328P to setup I2C.
// 1. GND -> GND
// 2. VCC -> VCC
// 3. SDA -> PC4 (pin 27)
// 4. SCL -> PC5 (pin 28)

// Declare a global LiquidCrystal_I2C object with I2C address (0x27), number of columns (16) and number of rows (2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:

  // Initialize the LCD
  lcd.init();
  lcd.backlight();
}

void loop() {
  // put your main code here, to run repeatedly:

  // Dispaly start menu
  showStartMenu(lcd);
  delay(2000); 

  // test case
  int score = 0;
  int time = 0; 

  for (int i = 0; i < 12; i++){
    // Show time and score on LCD display. Allow 1 second delay for display
    time = i;
    score = i/2;
    showScoreAndTime(lcd, score, time);
    delay(1000); 
  }

  // Dispaly Game Over
  showGameOver(lcd, score, time);
  delay(2000); 
}

