
// used pins
// SPI for bootloader: 1 (RESET), 17 (MOSI), 18 (MISO), 19 (SCK)
// SPI for OLED Display: 11 (CS),12 (DC),13 (RES),14 (CS),15 (RES),17 (MOSI),19 (SCK)
// I2C for LCD display: 27 (SDA),28 (SCL)
// USART for connecting ATMEGA328Ps: 2 (RX), 3 (TX)
// Audio Serial pins: 5 (TX) and 6 (RX)

// remaining pins
// 4, 16, 23 - 26

// STEP 1. Connect the following on the SN74HC595
// GND pin8  -> GND
// VCC pin16 -> VCC
// OE pin 13 -> GND
// MR pin 10 -> pin 26 (analog pin 3)
// DS (serial data input / data pin) pin 14 ->  pin 23 (analog pin 0)
// SH_CP (shift register clock / clock pin) pin 11 -> pin 24 (analog pin 1)
// ST_CP (storage register clock / latch pin) pin 12 -> pin 25 (analog pin 2) * connect a 10uF capacitor
// Connect a 1k resistors to pins 0 - 7 & 15 & LED

// STEP 2. Connect the Start button
// Button ->  4 / PD2 (digital Pin 2)
// Button -> VCC and 1k resistor & GND

//Pin connected to ST_CP of 74HC595
#define LATCH_PIN A2
//Pin connected to SH_CP of 74HC595
#define CLOCK_PIN A1
//Pin connected to DS of 74HC595
#define DATA_PIN  A0

// Pin define clear shift register 
#define CLEAR_PIN A3

//Pin connected to button
#define BUTTON_PIN 2

void setup() {
  //set pins to output so you can control the shift register
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLEAR_PIN, OUTPUT);

  // initialize the pushbutton pin as an input:
  pinMode(BUTTON_PIN, INPUT);

  // clear shift register
  digitalWrite(CLEAR_PIN, LOW);
  digitalWrite(CLEAR_PIN, HIGH);

  // Turn LED on for 5 seconds at first
  // get ready to store shift register (stores at rising edge)
  digitalWrite(LATCH_PIN, LOW);

  // shift out the bits:
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 4 /* number to display */);

  // store shift register
  digitalWrite(LATCH_PIN, HIGH);

  // pause before next value:
  delay(5000);

}

void loop() {

}
