// This program is used to test the sequence of the cockpit function when used in conjunction with 
// the motors and inputs modules. 

// ATMEGA328P Pinout
// SPI for bootloader: 1 (RESET), 17 (MOSI), 18 (MISO), 19 (SCK)
// SPI for OLED Display: 11 (CS),12 (DC),13 (RES),14 (CS),15 (RES),17 (MOSI),19 (SCK)
// I2C for LCD display: 27 (SDA),28 (SCL)
// USART for connecting ATMEGA328Ps: 2 (RX), 3 (TX)
// DFPlayer mini Audio Serial pins: 5 (TX) and 6 (RX)
// LED shift register: 6 (MR), 23 (serial data input), 24 (shift register clock), 25 (storage resiter clock)
// UART communication indicator : 4


/* Import required libaries */

// import LCD Display functions
#include "./Cockpit/LCD_Display.h"

// Declare a global LiquidCrystal_I2C object with I2C address (0x27), number of columns (16) and number of rows (2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// import OLED Display functions
#include "./Cockpit/OLED_display.h"

// Declaration for SSD1306 display connected using software SPI:
Adafruit_SSD1306 pitch_display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
Adafruit_SSD1306 roll_display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET_ROLL, OLED_CS_ROLL);


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

// import DFPlayer Mini library
#include "DFRobotDFPlayerMini.h"
#include <SoftwareSerial.h>

//Initialize the serial ports 
SoftwareSerial mySoftwareSerial(/*rx =*/4, /*tx =*/3);
DFRobotDFPlayerMini myDFPlayer;


void setup() {
    /****** LCD Display Initialization ******/
    lcd.init();
    lcd.backlight();

    /****** Set pins for LED shift register ******/
    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);
    pinMode(CLEAR_PIN, OUTPUT);

    // clear shift register
    digitalWrite(CLEAR_PIN, LOW);
    digitalWrite(CLEAR_PIN, HIGH);

    /****** Connector input pin ******/
    pinMode(CONNECTOR_PIN, INPUT); // 
    digitalWrite(CONNECTOR_PIN,LOW); // Disable internal pull up 

    /****** OLED Display initialization ******/
    // SSD1306_SWITCHCAPVCC = start display voltage from 3.3V internally
    if(!pitch_display.begin(SSD1306_SWITCHCAPVCC)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    };

    // Draw attitude indicator in static mode when the system starts up
    displayPitchIndicator_static(pitch_display);

    // start display voltage from 3.3V internally
    if(!roll_display.begin(SSD1306_SWITCHCAPVCC)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }

    // Draw attitude indicator in static mode when the system starts up
    displayRollIndicator_static(roll_display);

    /****** DFPlayer Mini Initialization ******/
    // begin serial communication with baud rate 9600
    mySoftwareSerial.begin(9600);
    
    //Set serial communictaion time out 500ms
    myDFPlayer.setTimeOut(500); 

    // define initial values
    myDFPlayer.begin(mySoftwareSerial); // set serial port for myDFPlayer
    myDFPlayer.EQ(0); //Normal Equalization
    myDFPlayer.volume(15);  //Set volume value (0~30).
  

}

void loop() {

    /***** Starting sequence  *****/
    // Display press start
    showStartMenu(lcd);
    delay(500); 

    // turn green LEDs on:
    // get ready to store shift register (stores at rising edge)
    digitalWrite(LATCH_PIN, LOW);

    // shift out the bits:
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 0x55 /* number to display */);

    // store shift register
    digitalWrite(LATCH_PIN, HIGH);

    // pause before next value:
    delay(500);

    // play "Press button to begin game" for 2 seconds 
    myDFPlayer.playFolder(1, 1);  
    delay(2000);

    // Set connector pin to low




}
