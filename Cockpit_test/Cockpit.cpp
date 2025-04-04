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
      // Serial.println(F("SSD1306 allocation failed"));
      for(;;); // Don't proceed, loop forever
  };

  // Draw attitude indicator in static mode when the system starts up
  displayPitchIndicator_static(pitch_display);

  // start display voltage from 3.3V internally
  if(!roll_display.begin(SSD1306_SWITCHCAPVCC)) {
      // Serial.println(F("SSD1306 allocation failed"));
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
  myDFPlayer.volume(15);  //Set volume value (0~30).

  // play "Press button to begin game" for 2 seconds 
  myDFPlayer.playFolder(folder, track);  
  delay(playback_time);

  // end serial communication
  Serial.end();
  
  delay(100);

  // set NMOS to stop passing signal
  digitalWrite(GATE_PIN, LOW);

  delay(100);
    
}

/****** Read UART ******/
void get_UART_signal(int parameter_array[]){

  // variables to store UART connection state
  int UART_state = digitalRead(CONNECTOR_PIN); 

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
void display_turn_dial_OLED(Adafruit_SSD1306 pitch_display, Adafruit_SSD1306 roll_display, int parameter_array[], int time){

  // turn 1 red LED on 
  // get ready to store shift register (stores at rising edge)
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 1);  // 1 = I
  digitalWrite(LATCH_PIN, HIGH);

  // SSD1306_SWITCHCAPVCC = start display voltage from 3.3V internally
  if(!pitch_display.begin(SSD1306_SWITCHCAPVCC)) {
      // Serial.println(F("SSD1306 allocation failed"));
      for(;;); // Don't proceed, loop forever
  }
  
  //change the pitch indicator 
  for (int pitch = 0; pitch <= parameter_array[1]; pitch++){
    displayPitchIndicator_transient(pitch_display,pitch);
    delay(100);
  }

  // start display voltage from 3.3V internally
  if(!roll_display.begin(SSD1306_SWITCHCAPVCC)) {
      // Serial.println(F("SSD1306 allocation failed"));
      for(;;); // Don't proceed, loop forever
  }

  //change the roll indicator 
  for (int roll = 0; roll <= parameter_array[2]; roll++){
    displayRollIndicator_transient(roll_display,roll);
    delay(100);
  }


  // play "Rotate Selector" for 2 seconds
  Speaker_output(2,5, 2000);

  // Show current score and time
  //showScoreAndTime(lcd, parameter_array[0], time);

    // keep delays as they are important 
  delay(3000);
}

/***** Turn dial cockpit display *****/
void display_move_joystick_OLED(char direction, Adafruit_SSD1306 pitch_display, Adafruit_SSD1306 roll_display, int parameter_array[], int time){

  // turn 2 red LEDs on 
  // get ready to store shift register (stores at rising edge)
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 3); // 3 = II
  digitalWrite(LATCH_PIN, HIGH);

  // SSD1306_SWITCHCAPVCC = start display voltage from 3.3V internally
  if(!pitch_display.begin(SSD1306_SWITCHCAPVCC)) {
      // Serial.println(F("SSD1306 allocation failed"));
      for(;;); // Don't proceed, loop forever
  }
  
  //change the pitch indicator 
  for (int pitch = 0; pitch <= parameter_array[1]; pitch++){
    displayPitchIndicator_transient(pitch_display,pitch);
    delay(100);
  }

  // start display voltage from 3.3V internally
  if(!roll_display.begin(SSD1306_SWITCHCAPVCC)) {
      // Serial.println(F("SSD1306 allocation failed"));
      for(;;); // Don't proceed, loop forever
  }

  //change the roll indicator 
  for (int roll = 0; roll <= parameter_array[2]; roll++){
    displayRollIndicator_transient(roll_display,roll);
    delay(100);
  }

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

  // Show current score and time
  //showScoreAndTime(lcd, parameter_array[0], time);

  // keep delays as they are important 
  delay(3000);
}

/***** Press button cockpit display *****/
void display_press_button_OLED(Adafruit_SSD1306 pitch_display, Adafruit_SSD1306 roll_display, int parameter_array[], int time){

  // turn 3 red LEDs on 
  // get ready to store shift register (stores at rising edge)
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 7);  // 7 = III
  digitalWrite(LATCH_PIN, HIGH);

  // SSD1306_SWITCHCAPVCC = start display voltage from 3.3V internally
  if(!pitch_display.begin(SSD1306_SWITCHCAPVCC)) {
      // Serial.println(F("SSD1306 allocation failed"));
      for(;;); // Don't proceed, loop forever
  }
  
  //change the pitch indicator 
  for (int pitch = 0; pitch <= parameter_array[1]; pitch++){
    displayPitchIndicator_transient(pitch_display,pitch);
    delay(100);
  }

  // start display voltage from 3.3V internally
  if(!roll_display.begin(SSD1306_SWITCHCAPVCC)) {
      // Serial.println(F("SSD1306 allocation failed"));
      for(;;); // Don't proceed, loop forever
  }

  //change the roll indicator 
  for (int roll = 0; roll <= parameter_array[2]; roll++){
    displayRollIndicator_transient(roll_display,roll);
    delay(100);
  }

  // play "Press Button" for 1 second
  Speaker_output(2,6, 1000);

  // Show current score and time
  //showScoreAndTime(lcd, parameter_array[0], time);

  // keep delays as they are important 
  delay(3000);
}


/***** Game Over cockpit display *****/
void display_game_over_OLED(Adafruit_SSD1306 pitch_display, Adafruit_SSD1306 roll_display,int parameter_array[],int time){

  // turn 4 red LEDs on 
  // get ready to store shift register (stores at rising edge)
  digitalWrite(LATCH_PIN, LOW);
  shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 15);  // 15 = IIII
  digitalWrite(LATCH_PIN, HIGH);
  
  // Show game over screen on OLED display

  // SSD1306_SWITCHCAPVCC = start display voltage from 3.3V internally
  if(!pitch_display.begin(SSD1306_SWITCHCAPVCC)) {
      // Serial.println(F("SSD1306 allocation failed"));
      for(;;); // Don't proceed, loop forever
  }

  //change the pitch indicator 
  displayPitchIndicator_transient(pitch_display,parameter_array[1]);

  // start display voltage from 3.3V internally
  if(!roll_display.begin(SSD1306_SWITCHCAPVCC)) {
      // Serial.println(F("SSD1306 allocation failed"));
      for(;;); // Don't proceed, loop forever
  }
  
  //change the roll indicator 
  displayRollIndicator_transient(roll_display,parameter_array[2]);

  // keep delays as they are important 
  delay(3000);
}

/****** Game Over LCD Display ******/
void display_game_over_LCD(LiquidCrystal_I2C lcd, int score,int time){
    
  // clear LCD at the beginning of the function call
  lcd.clear();

  // Print the message: "Game Over"
  lcd.setCursor(0,0);
  lcd.print("   GAME OVER");
  
  // Convert Seconds into XX:XX (Minutes:Seconds)
  int minute = time / 60;
  int second = time % 60;  
  
  // define string to store current time
  String currentTime;
  
  if ((minute < 10) && (second < 10)){
      currentTime = "0" + String(minute) + ":" + "0" + String(second);
  }else if (minute < 10){
      currentTime = "0" + String(minute) + ":" + String(second);
  }else if (second < 10){
      currentTime = String(minute) + ":" + "0" + String(second);
  }else{
      currentTime = String(minute) + ":" + String(second);
  }
  
  // Print the score and time as "Score:XX (XX:XX)"
  String scoreAndTime = "Score:" + String(score) + " (" + currentTime +")";
  lcd.setCursor(0,1);
  lcd.print(scoreAndTime);
}



/***** Wait for Start Button to be pressed *****/
void notify_start_button_pressed(){
  // variables for debouncing 
  int start_button_state = digitalRead(START_PIN);
  int last_button_state = LOW;
  unsigned long last_debounce_time = 0;
  unsigned long debounce_delay = 50;

  while (start_button_state == HIGH){
    int reading = digitalRead(START_PIN);
    if (reading != last_button_state){
      last_debounce_time = millis();
    }

    // if the reading has been there longer than the debounce break from while loop
    if ((millis() - last_debounce_time) > debounce_delay){
      start_button_state = reading;
    }
  }

  // Set connector pin to output to notify Luke's board that the start button was pressed
  digitalWrite(CONNECTOR_PIN,HIGH);
  delay(500);
  digitalWrite(CONNECTOR_PIN,LOW);
  delay(500);
  // Set connector pin to input and pulled up to high internally
  pinMode(CONNECTOR_PIN, INPUT_PULLUP);
}