// connect to header file
#include "./Cockpit.h"

void LED_startup(){
  /****** Set pins for LED shift register ******/
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLEAR_PIN, OUTPUT);

  // clear shift register
  digitalWrite(CLEAR_PIN, LOW);
  digitalWrite(CLEAR_PIN, HIGH);

  // turn 4 red LEDs on
  // get ready to store shift register (stores at rising edge)
  digitalWrite(LATCH_PIN, LOW);
  
  // shift out the bits (15 = 1111 )
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 15); 

  // store shift register
  digitalWrite(LATCH_PIN, HIGH);

}

/****** OLED Display initialization ******/
void OLED_startup(Adafruit_SSD1306 pitch_display, Adafruit_SSD1306 roll_display){
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
}

/****** LCD Display Initialization ******/
void LCD_startup(LiquidCrystal_I2C lcd){

  lcd.init();
  lcd.backlight();

  // Display press start
  showStartMenu(lcd);
}

/****** DFPlayer Mini Initialization ******/
void Speaker_output(int folder, int track, int playback_time){

  // set NMOS to pass signal
  pinMode(GATE_PIN, OUTPUT);
  digitalWrite(GATE_PIN, HIGH);
  delay(500);

  // begin serial communication with baud rate 9600
  Serial.begin(9600);

  // Declare struct for DFPlayer mini. Note: this cannot be added as a global variable
  DFRobotDFPlayerMini myDFPlayer;

  //Set serial communictaion time out 500ms
  myDFPlayer.setTimeOut(500); 

  // define initial values
  myDFPlayer.begin(Serial); // set serial port for myDFPlayer
  myDFPlayer.EQ(0); //Normal Equalization
  myDFPlayer.volume(20);  //Set volume value (0~30).

  // play "Press button to begin game" for 2 seconds 
  myDFPlayer.playFolder(folder, track);  
  delay(playback_time);

  // end serial communication
  Serial.end();
  
  delay(100);

  // set NMOS to stop passing signal
  digitalWrite(GATE_PIN, LOW);
    
}

/****** Read UART ******/
void get_UART_signal(int parameter_array[4]){

  // variables to store UART connection state
  int UART_state = HIGH; 

  // array to store the UART signals for [score, pitch, roll, device]
  byte UART_signal_array[4]; 

  // Wait to read serial port & connector pin to become LOW
  while (UART_state == HIGH){
    // if UART_state is HIGH -> remain in wait mode
    UART_state =  digitalRead(CONNECTOR_PIN);
  };

  // if UART_state is LOW -> begin serial communication
  Serial.begin(9600);

  // read bytes only when reaceiving data
  if (Serial.available() > 0){
    // read the UART signal until it reaches 4 bytes 
    Serial.readBytes(UART_signal_array, sizeof(UART_signal_array));
  }

  // end Serial communication
  Serial.end();

  // get score, pitch, roll, and device
  for (int i = 0; i< sizeof(UART_signal_array);i++){
    parameter_array[i] = (int)UART_signal_array[i];
  }

}

/***** Turn dial cockpit display *****/
void display_turn_dial(Adafruit_SSD1306 pitch_display, Adafruit_SSD1306 roll_display, LiquidCrystal_I2C lcd, int parameter_array[4], int time){

  // turn 1 red LED on 
  // get ready to store shift register (stores at rising edge)
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 1);  // 1 = I
  digitalWrite(LATCH_PIN, HIGH);

  // Show current score and time
  showScoreAndTime(lcd, parameter_array[0], time);
  
  //change the pitch indicator 
  displayPitchIndicator_transient(pitch_display,parameter_array[1]);

  //change the roll indicator 
  displayRollIndicator_transient(roll_display,parameter_array[2]);

  // play "Rotate Selector" for 2 seconds
  Speaker_output(2,5, 2000);
}

/***** Turn dial cockpit display *****/
void display_move_joystick(char direction, Adafruit_SSD1306 pitch_display, Adafruit_SSD1306 roll_display, LiquidCrystal_I2C lcd, int parameter_array[4], int time){

  // turn 2 red LEDs on 
  // get ready to store shift register (stores at rising edge)
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 3); // 3 = II
  digitalWrite(LATCH_PIN, HIGH);

  // Show current score and time
  showScoreAndTime(lcd, parameter_array[0], time);
  
  //change the pitch indicator 
  displayPitchIndicator_transient(pitch_display,parameter_array[1]);

  //change the roll indicator 
  displayRollIndicator_transient(roll_display,parameter_array[2]);

  // play audio
  switch (direction){
    case 'u': // pull up
      Speaker_output(2,3, 1000);
      break;
    case 'd': // pull down
      Speaker_output(2,4, 1000);
      break;
    case 'l': // turn left
      Speaker_output(2,2, 1000);
      break;
    case 'r': // turn right
      Speaker_output(2,1, 1000);
      break;
    default: // engine sound for 5 seconds
      Speaker_output(1,3, 5000);
      break;
  } 
}

/***** Press button cockpit display *****/
void display_press_button(Adafruit_SSD1306 pitch_display, Adafruit_SSD1306 roll_display, LiquidCrystal_I2C lcd, int parameter_array[4], int time){

  // turn 3 red LEDs on 
  // get ready to store shift register (stores at rising edge)
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 7);  // 7 = III
  digitalWrite(LATCH_PIN, HIGH);

  // Show current score and time
  showScoreAndTime(lcd, parameter_array[0], time);
  
  //change the pitch indicator 
  displayPitchIndicator_transient(pitch_display,parameter_array[1]);

  //change the roll indicator 
  displayRollIndicator_transient(roll_display,parameter_array[2]);

  // play "Press Button" for 1 second
  Speaker_output(2,6, 1000);
}


/***** Game Over cockpit display *****/
void display_game_over(Adafruit_SSD1306 pitch_display, Adafruit_SSD1306 roll_display, LiquidCrystal_I2C lcd, int parameter_array[4], int time){

  // turn 4 red LEDs on 
  // get ready to store shift register (stores at rising edge)
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 15);  // 15 = IIII
  digitalWrite(LATCH_PIN, HIGH);

  // Show game over screen on LCD display
  showGameOver(lcd, parameter_array[0], time);
  
  //change the pitch indicator 
  displayPitchIndicator_transient(pitch_display,parameter_array[1]);

  //change the roll indicator 
  displayRollIndicator_transient(roll_display,parameter_array[2]);

  // play "Press Button" for 1 second
  Speaker_output(1,4, 1000);
}