// This program is used to test the sequence of the cockpit function when used in conjunction with 
// the motors and inputs modules. 

// import LCD Display functions
#include "./LCD_Display.h"

// Declare a global LiquidCrystal_I2C object with I2C address (0x27), number of columns (16) and number of rows (2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// import OLED Display functions
#include "./OLED_display.h"

// Declaration for SSD1306 display connected using software SPI:
Adafruit_SSD1306 pitch_display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
Adafruit_SSD1306 roll_display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET_ROLL, OLED_CS_ROLL);

// import OLED Display functions
#include "./Speaker.h"

//Initialize the serial ports 
SoftwareSerial mySoftwareSerial(/*rx =*/4, /*tx =*/3);
DFRobotDFPlayerMini myDFPlayer;

// Connect to headerfile
#include "./Cockpit.h"

void setup() {
   
    // move to start up state
    cockpit_startup(lcd,pitch_display,roll_display,mySoftwareSerial,myDFPlayer);

}

void loop() {

    // Wait to read serial port & connector pin to be HIGH
}
