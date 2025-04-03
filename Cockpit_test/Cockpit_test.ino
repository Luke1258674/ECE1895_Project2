// This program is used to test the sequence of the cockpit function when used in conjunction with 
// the motors and inputs modules. 

// Connect to headerfile
#include "./Cockpit.h"

// Declare a global LiquidCrystal_I2C object with I2C address (0x27), number of columns (16) and number of rows (2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Declaration for SSD1306 display connected using software SPI:
Adafruit_SSD1306 pitch_display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
Adafruit_SSD1306 roll_display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET_ROLL, OLED_CS_ROLL); 

// variables to store current score, pitch angle, roll angle, and input device used
int parameter_array[4] = {0,0,0,0};

// variables to store time since the game began (milli-seconds)
unsigned long beginTime = 0;
unsigned long currentTime = 0;
int time = 0;

void setup() {

  // move OLED to start up state
  OLED_startup(pitch_display, roll_display);

  // move LCD to start up state
  LCD_startup(lcd);

  // Move LEDs to start up state
  LED_startup();
  
  // move DFPlayer Mini to start up state
  Speaker_output(1, 1, 2000);

  // Set connector pin to input and pulled up to high internally
  pinMode(CONNECTOR_PIN, INPUT_PULLUP);

}

void loop() {

  // wait for UART signal to arrive 
  get_UART_signal(parameter_array);

  // start timer only for the first loop
  if (beginTime == 0){
    beginTime = millis();
  }

  // get the time when the function was called
  currentTime = millis();
  time = int((currentTime - beginTime) / 1000);

  // Select action (device = 1: turn dial, device = 2: joystick, device = 3: press button, device = 4: game over) 
  if (parameter_array[3] == 1){
    // turn the dial motion: audio output, LED, LCD display, and OLED display
    display_turn_dial(pitch_display, roll_display, lcd, parameter_array, time); 

  }else if (parameter_array[3] == 2){

    // determine direction
    char direction; 
    if (parameter_array[1] > 0){
      // if pitch > 0and roll = 0 direct user to pull down
      direction = 'd';
    }else if(parameter_array[1] < 0){
      // if pitch < 0 and roll = 0 direct user to pull down
      direction = 'u';
    }else if (parameter_array [2] > 0){
      // if pitch is 0 and roll > 0 direct user to turn left
      direction = 'l';
    }else if (parameter_array [2] < 0){
      // if pitch is 0 and roll > 0 direct user to turn left
      direction = 'r';
    }else{
      // default is pull up
      direction = 'u'; 
    }

    // Move joystick motion: audio output, LED, LCD display, and OLED display
    display_move_joystick(direction, pitch_display, roll_display, lcd, parameter_array, time);

  }else if (parameter_array[3] == 3){
    // turn the press button: audio output, LED, LCD display, and OLED display
    display_press_button(pitch_display, roll_display, lcd, parameter_array, time); 

  }else if (parameter_array[3] == 4){
    // display game over screen
    display_game_over(pitch_display, roll_display, lcd, parameter_array, time); 

  }else{
    // default: engine sound for 5 seconds
    Speaker_output(1,3, 5000);

    // delay for 3 seconds
    delay(3000);

    // move back to setup()
    setup();

  }
}
