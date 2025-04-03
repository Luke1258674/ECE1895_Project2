
// used pins
// SPI for bootloader: 1 (RESET), 17 (MOSI), 18 (MISO), 19 (SCK)
// SPI for OLED Display: 11 (CS),12 (DC),13 (RES),14 (CS),15 (RES),17 (MOSI),19 (SCK)
// I2C for LCD display: 27 (SDA),28 (SCL)
// USART for connecting ATMEGA328Ps: 2 (RX), 3 (TX)
// Audio Serial pins: 5 (TX) and 6 (RX)

// remaining pins
// 4, 16, 23 - 26

// STEP 1. Install the library needed to run the DFRObot DFPlayer Mini
#include "DFRobotDFPlayerMini.h"
#include <SoftwareSerial.h>


// STEP 2. Connect the following pins for USART for DFPlayer Mini
// VCC  -> VCC
// RX   -> pin5 (PB2) TX add 1k resistor --- digital pin 3 in Arduino
// TX   -> pin6 (PD0) RX --- digital pin 4 in Arduino
// SPK_1-> Speaker input
// SPK_2-> Speaker output
// GND  -> GND 


//Initialize the serial ports 
SoftwareSerial mySoftwareSerial(/*rx =*/4, /*tx =*/3); // RX on Arduino, TX on Arduino
DFRobotDFPlayerMini myDFPlayer;

void setup() {
  // begin serial communication with baud rate 9600
  mySoftwareSerial.begin(9600);
  
  //Set serial communictaion time out 500ms
  myDFPlayer.setTimeOut(500); 

  // define initial values
  myDFPlayer.begin(mySoftwareSerial); // set serial port for myDFPlayer
  myDFPlayer.EQ(0); //Normal Equalization
  myDFPlayer.volume(15);  //Set volume value (0~30).

  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)

  // play "Press button to begin game" for 2 seconds 
  myDFPlayer.playFolder(1, 1);  
  delay(2000);

  // Play Engine Startup sound for 10 seconds
  myDFPlayer.playFolder(1, 2);  
  delay(10000);

  // play Engine background sound for 10 seconds
  myDFPlayer.playFolder(1, 3);  
  delay(10000);

  // play "Game ended"
  myDFPlayer.playFolder(1, 4); 
  delay(1000); 

  // play "Turn right"
  myDFPlayer.playFolder(2, 1);  
  delay(1000);

  // play "Turn left"
  myDFPlayer.playFolder(2, 2); 
  delay(1000);

  // play "Pull Up"
  myDFPlayer.playFolder(2, 3); 
  delay(1000);

  // play "Pull Down"
  myDFPlayer.playFolder(2, 4);
  delay(1000);

  // play "Rotate Selector" for 2 seconds
  myDFPlayer.playFolder(2, 5);
  delay(2000);

  // play "Press Button"
  myDFPlayer.playFolder(2, 6);
  delay(1000);

}

void loop() {


}
