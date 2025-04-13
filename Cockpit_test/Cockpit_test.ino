// This program is used to test the sequence of the cockpit function when used in conjunction with 
// the motors and inputs modules. 

// Connect to headerfile
#include "./Cockpit.h"

// Declare a global LiquidCrystal_I2C object with I2C address (0x27), number of columns (16) and number of rows (2)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Declaration for SSD1306 display connected using software SPI:
Adafruit_SSD1306 pitch_display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
Adafruit_SSD1306 roll_display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET_ROLL, OLED_CS_ROLL); 

// variables to store time and score since the game began (milli-seconds)
unsigned long beginTime;
unsigned long currentTime;
int time = 0; 
int score = 0;
int previous_score;
bool start_of_game;
bool game_over;

// variables for UART communication
Command cmd;
bool newData;

void setup() {

  // set gameline pin to output mode (default is High) *TOP PRIORITY
  pinMode(GAMELINE_PIN,OUTPUT);
  digitalWrite(GAMELINE_PIN,LOW);

  // NMOS gate pin initialization 
  pinMode(GATE_PIN, OUTPUT);
  digitalWrite(GATE_PIN, LOW);

  // start pin initialization 
  pinMode(START_PIN,INPUT_PULLUP);

  // Play Engine Startup sound for 10 seconds
  // myDFPlayer.playFolder(1, 2,10000);  

  // move OLED to start up state
  OLED_startup(pitch_display, roll_display);

  // move LCD to start up state
  LCD_startup(lcd);

  delay(1000);

  // Move LEDs to start up state (all LEDs are on)
  LED_startup();

  // begin Serial at Baud rate 9600 *TOP PRIORITY
  Serial.begin(9600);

  delay(1000);

  // move DFPlayer Mini to start up state
  Speaker_output(1, 1, 2000);

  // start timer only for the first loop
  beginTime = millis();

  // set start of game flag to true
  start_of_game = true;
}

void loop() {

  // turn 1 red LEDs on
  digitalWrite(LATCH_PIN, LOW);   // get ready to store shift register (stores at rising edge)
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 1);   // shift out the bits 
  digitalWrite(LATCH_PIN, HIGH);   // store shift register

  // Wait for the start button to be pressed. 
  // Once pressed, send a HIGH signal to the game line pin. 
  if (start_of_game == true){
    notify_start_button_pressed();
    // update flag to check if it is the start of the game
    start_of_game = false;
  }else{
    // delay in place to align timing
    delay(1000);
  }

  // debug
  // notify_start_button_pressed();

  // if is the second iteration there after, just turn the game line pin HIGH to wait for new signal
  digitalWrite(GAMELINE_PIN, HIGH);

  // initialize new data flag
  newData = false;

  // wait for UART signal to arrive 
  while(newData == false){
    // turns game line LOW once received data
    get_UART_signal(cmd, newData);

    delay(100);

    // turn 2 red LEDs on
    digitalWrite(LATCH_PIN, LOW);   // get ready to store shift register (stores at rising edge)
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 3);   // shift out the bits 
    digitalWrite(LATCH_PIN, HIGH);   // store shift register
  }

  // UART error handling to adjust values for LCD display 
  // adjust score
  if (( cmd.score > 100) || ( cmd.score < 0)){ 
    cmd.score = previous_score + 1;
    previous_score = cmd.score;  
  }else{ 
    previous_score = cmd.score;                          
  }

  // get time
  time = ((millis() - beginTime) / 1000);

  // UART error handling for time on LCD display 
  if ((time > 3600) || (time < 0)){ 
    time = cmd.score * 5; 
  }

  // adjust other parameters
  if ((cmd.yaw > 50) || (cmd.yaw < -50)){
    cmd.yaw = 0;
  }

  int pitch = cmd.pitch;
  if ((cmd.pitch > 50) || (cmd.pitch < -50)){
    cmd.roll = 0;
  }

  int roll = cmd.roll;
  if ((cmd.roll > 50) || (cmd.roll < -50)){
    cmd.roll = 0;
  }

  // Select process based on device used
  if (cmd.device_used == 1){
    // turn 1 green LEDs on
    digitalWrite(LATCH_PIN, LOW);   // get ready to store shift register (stores at rising edge)
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 16);   // shift out the bits 
    digitalWrite(LATCH_PIN, HIGH);   // store shift register

    // Audio for "turn left"
    Speaker_output(2,2, 1000);

  }else if (cmd.device_used == 2){
    // turn 2 green LEDs on
    digitalWrite(LATCH_PIN, LOW);   // get ready to store shift register (stores at rising edge)
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 32);   // shift out the bits 
    digitalWrite(LATCH_PIN, HIGH);   // store shift register

    // Audio for "turn right"
    Speaker_output(2,1, 1000);

  }else if (cmd.device_used == 3){
    // turn 3 green LEDs on
    digitalWrite(LATCH_PIN, LOW);   // get ready to store shift register (stores at rising edge)
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 64);   // shift out the bits 
    digitalWrite(LATCH_PIN, HIGH);   // store shift register

    // Audio for "Pull up"
    Speaker_output(2,3, 1000);
    
  }else if (cmd.device_used == 4){
    // turn 4 green LEDs on
    digitalWrite(LATCH_PIN, LOW);   // get ready to store shift register (stores at rising edge)
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 128);   // shift out the bits 
    digitalWrite(LATCH_PIN, HIGH);   // store shift register

    // Audio for "Pull down"
    Speaker_output(2,4, 1000);

  }else if (cmd.device_used == 5){
    // play "Press Button" for 1 second
    Speaker_output(2,6, 1000);

  }else{

    // turn 4 red LEDs on
    digitalWrite(LATCH_PIN, LOW);   // get ready to store shift register (stores at rising edge)
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 15);   // shift out the bits 
    digitalWrite(LATCH_PIN, HIGH);   // store shift register
    
    // play "game ended" 
    Speaker_output(1,4, 1000);
    game_over = true;
  }

  // debug
  debug(lcd, cmd);
  delay(1000);

  // display LCD
  if (game_over == false){
    showScoreAndTime(lcd,cmd.score,time);
  }else{
    showGameOver(lcd, cmd.score, time);
    OLED_end(pitch_display, roll_display);
    // go back to push start button
    start_of_game = true;

    // reset game_over flag
    game_over = true;
  }

  delay(1000);

  // turn 3 red LEDs on
  digitalWrite(LATCH_PIN, LOW);   // get ready to store shift register (stores at rising edge)
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 7);   // shift out the bits 
  digitalWrite(LATCH_PIN, HIGH);   // store shift register

  delay(1000);

  
}