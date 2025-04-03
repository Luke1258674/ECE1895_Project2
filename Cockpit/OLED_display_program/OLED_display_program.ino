
// Step 1. Install the following library from Library manager
// Adafrui_SSD1306.h (The Adafruit_GFX) library will come along as a dependant library to this library)

// Step 2. Connect the first 0.96" display with the Atmega328P using the following pins to set up SPI
// GND -> GND
// VCC -> VCC (3.3V or 5V)
// D0 (SCK)  ->  pin19 (PB5)
// D1 (MOSI) ->  pin17 (PB3)
// RES -> pin13
// DC (Data / Connect) -> pin12
// CS (chip select) -> pin11

// Step 3. Connect the second 0.96" display with the Atmega328P using the following pins to set up SPI
// GND -> GND
// VCC -> VCC (3.3V or 5V)
// D0 (SCK)  ->  pin19 (PB5)
// D1 (MOSI) ->  pin17 (PB3)
// RES -> pin15
// DC (Data / Connect) -> pin12
// CS (chip select) -> pin14

// conenct to the header file 
#include "./OLED_display.h"

// Declaration for SSD1306 display connected using software SPI:
Adafruit_SSD1306 pitch_display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
Adafruit_SSD1306 roll_display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET_ROLL, OLED_CS_ROLL);

void setup() {

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

  /*
  // Draw attitude indicator in transient mode where it changes based on pitch
  int pitch = 0;
  int roll = 0;
  for (pitch; pitch < 20; pitch++){
    roll = pitch;
    displayPitchIndicator_transient(pitch_display, pitch);
    displayRollIndicator_transient(roll_display, roll);
  }

  for (pitch; pitch > -20; pitch--){
    roll = pitch;
    displayPitchIndicator_transient(pitch_display, pitch);
    displayRollIndicator_transient(roll_display, roll);
  }
  */

}

void loop() {
}

