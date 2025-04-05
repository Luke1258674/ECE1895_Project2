// This program is used to test the sequence of the cockpit function when used in conjunction with 
// the motors and inputs modules. 

// Connect to headerfile
#include "./Cockpit.h"

// Declare a global LiquidCrystal_I2C object with I2C address (0x27), number of columns (16) and number of rows (2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Declaration for SSD1306 display connected using software SPI:
Adafruit_SSD1306 pitch_display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
Adafruit_SSD1306 roll_display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET_ROLL, OLED_CS_ROLL); 

// variables to store time since the game began (milli-seconds)
unsigned long beginTime;
unsigned long currentTime;
int time; 

// variables for UART communication
Command cmd;
bool newData = false;

void setup() {

  // set gameline pin to output mode (default is High) *TOP PRIORITY
  pinMode(GAMELINE_PIN,OUTPUT);
  digitalWrite(GAMELINE_PIN,LOW);

  // begin Serial at Baud rate 9600 *TOP PRIORITY
  Serial.begin(9600);

  // NMOS gate pin initialization 
  pinMode(GATE_PIN, OUTPUT);
  digitalWrite(GATE_PIN, LOW);

  // start pin initialization 
  pinMode(START_PIN,INPUT_PULLUP);

  // move LCD to start up state
  LCD_startup(lcd);

  // move OLED to start up state
  OLED_startup(pitch_display, roll_display);

  // Move LEDs to start up state (all LEDs are on)
  LED_startup();

  // move DFPlayer Mini to start up state
  //Speaker_output(1, 1, 2000);

}

void loop() {

  // initialize new data flag
  newData = false;

  // turn 1 red LEDs on
  digitalWrite(LATCH_PIN, LOW);   // get ready to store shift register (stores at rising edge)
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 1);   // shift out the bits 
  digitalWrite(LATCH_PIN, HIGH);   // store shift register

  // Wait for the start button to be pressed. 
  // Once pressed, send a HIGH signal to the game line pin. 
  notify_start_button_pressed();

  // wait for UART signal to arrive 
  while(newData == false){

    // turns game line LOW once received data
    get_UART_signal(cmd, newData);

    // turn 2 red LEDs on
    digitalWrite(LATCH_PIN, LOW);   // get ready to store shift register (stores at rising edge)
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 3);   // shift out the bits 
    digitalWrite(LATCH_PIN, HIGH);   // store shift register
  }

  // start timer only for the first loop
  beginTime = millis();
  
  // Display process

  if(newData == true){
    debug(lcd, cmd);
  }

  // turn 3 red LEDs on
  digitalWrite(LATCH_PIN, LOW);   // get ready to store shift register (stores at rising edge)
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 7);   // shift out the bits 
  digitalWrite(LATCH_PIN, HIGH);   // store shift register

  delay(100);

    /*
    // get the time when the function was called
    currentTime = millis();
    time = (int)((currentTime - beginTime) / 1000);

    // debug
    // turn 1 red LEDs on
    // get ready to store shift register (stores at rising edge)
    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, game_count); 
    digitalWrite(LATCH_PIN, HIGH);
    // debug

    delay(500);
  

    // debug 
    parameter_array[0] = game_count * 10; // update score 
    parameter_array[1] = game_count * 5; // update pitch
    parameter_array[2] = game_count * 10; // update roll 
    parameter_array[3] = game_count; // update selection
    game_count++;
    // debug

    delay(500);
    // Select action (device = 1: turn dial, device = 2: joystick, device = 3: press button, device = 4: game over) 
    if (parameter_array[3] == 1){
      
      // turn the dial motion: audio output, LED, LCD display, and OLED display
      display_turn_dial_OLED(pitch_display, roll_display, parameter_array, time); 

      // display score & time on LCD display

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

      // Move joystick motion: audio output, LED, and OLED display
      display_move_joystick_OLED(direction, pitch_display, roll_display, parameter_array, time);

      // display score & time on LCD display
      

    }else if (parameter_array[3] == 3){

      // turn the press button: audio output, LED, LCD display, and OLED display
      display_press_button_OLED(pitch_display, roll_display, parameter_array, time); 


    }else if (parameter_array[3] == 4){

      // display game over screen on OLED display and turn on all red LEDs
      display_game_over_OLED(pitch_display,roll_display, parameter_array,time);
      
      // display game over screen on LCD display
      //display_game_over_LCD(lcd,score,time);

      // delay for 3 seconds
      delay(3000);

      // Speaker outputs "Press Button to begin game"
      Speaker_output(1, 1, 2000);

      // Wait for the start button to be pressed. Once pressed, send a HIGH signal to the connector pin. 
      notify_start_button_pressed();

    }else{
      // default: engine sound for 3 seconds
      Speaker_output(1,3, 3000);

      // delay for 3 seconds
      delay(3000);

    }
    */

}