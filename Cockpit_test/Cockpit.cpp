#include "Arduino.h"
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

}



/****** OLED Display initialization ******/
void OLED_startup(Adafruit_SSD1306 &pitch_display, Adafruit_SSD1306 &roll_display){

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

/****** OLED Display initialization ******/
void OLED_end(Adafruit_SSD1306 &pitch_display, Adafruit_SSD1306 &roll_display){

  // SSD1306_SWITCHCAPVCC = start display voltage from 3.3V internally
  if(!pitch_display.begin(SSD1306_SWITCHCAPVCC)) {
      // Serial.println(F("SSD1306 allocation failed"));
      for(;;); // Don't proceed, loop forever
  };

  // Attitude indicator starting sequence at the beginning of the game
  for (int intro_value = 0; intro_value < 5; intro_value++){
    displayPitchIndicator_transient(pitch_display, intro_value);
    delay(50);
  }
  for (int intro_value = 5; intro_value > -5; intro_value--){
    displayPitchIndicator_transient(pitch_display, intro_value);
    delay(50);
  }
  for (int intro_value = -5; intro_value < 0; intro_value++){
  displayPitchIndicator_transient(pitch_display, intro_value);
  delay(50);
  }

  // start display voltage from 3.3V internally
  if(!roll_display.begin(SSD1306_SWITCHCAPVCC)) {
      // Serial.println(F("SSD1306 allocation failed"));
      for(;;); // Don't proceed, loop forever
  }

  // Roll indicator starting sequence at the beginning of the game
  for (int intro_value = 0; intro_value < 5; intro_value++){
    displayRollIndicator_transient(roll_display,intro_value);
    delay(50);
  }
  for (int intro_value = 5; intro_value > -5; intro_value--){
    displayRollIndicator_transient(roll_display,intro_value);
    delay(50);
  }
    for (int intro_value = -5; intro_value < 0; intro_value++){
    displayRollIndicator_transient(roll_display,intro_value);
    delay(50);
  }

}

/****** LCD Display Initialization ******/
void LCD_startup(LiquidCrystal_I2C &lcd){

  lcd.init();
  lcd.backlight();

  // Display press start
  showStartMenu(lcd);

}

/****** DFPlayer Mini Initialization ******/
void Speaker_output(int folder, int track, int playback_time){

  // begin Serial at Baud rate 9600 *TOP PRIORITY
  //Serial.begin(9600);

  // set NMOS to pass signal
  digitalWrite(GATE_PIN, HIGH);
  delay(100);

  // Declare struct for DFPlayer mini. Note: this cannot be added as a global variable
  DFRobotDFPlayerMini myDFPlayer;

  //Set serial communictaion time out 100ms
  myDFPlayer.setTimeOut(100); 

  // define initial values
  myDFPlayer.begin(Serial); // set serial port for myDFPlayer
  myDFPlayer.EQ(0); //Normal Equalization
  myDFPlayer.volume(25);  //Set volume value (0~30).

  // play "Press button to begin game" for 2 seconds 
  myDFPlayer.playFolder(folder, track);  
  delay(playback_time);
  
  delay(100);

  // set NMOS to stop passing signal
  digitalWrite(GATE_PIN, LOW);

  delay(100);

  // clear buffer in serial
  Serial.flush();
    
}

/****** Read UART ******/
void get_UART_signal(Command& cmd, bool& newData){

  // reference: https://forum.arduino.cc/t/simple-code-to-send-a-struct-between-arduinos-using-serial/672196

  // store data length
  const byte startMarker = 23;
  const byte rxDataLen = sizeof(cmd);
  static byte recvData[rxDataLen];
  byte rb;
  byte* structStart;
  structStart = reinterpret_cast<byte*> (&cmd);

  if ((Serial.available() >= rxDataLen + 1) && (newData == false)){
    rb = Serial.read();

    if (rb == startMarker){
      // copy teh bytes to the struct
      for (byte n = 0; n < rxDataLen; n++){
        *(structStart + n) = Serial.read();
      }
      // make sure there is no garbage left in the buffer
      while (Serial.available() > 0){
        byte dumpTheData = Serial.read();
      }

      delay(100);

      // turn game line pin back to low once data is received
      digitalWrite(GAMELINE_PIN, LOW);

      // update bool to track if new data has arrived
      newData = true;

      // clear buffer in serial
      //Serial.flush();

      delay(100);
    }
  }

  // UART error handling, if UART signal does not arrive after 0.1 second, move on using default value
    /*
    if ((millis() - UART_start_time) > 100){
      cmd.score = previous_score;
      cmd.device_used = 5;

      // turn game line pin back to low once data is received
      digitalWrite(GAMELINE_PIN, LOW);

      // update bool to track if new data has arrived
      newData = true;

      // clear buffer in serial
      Serial.flush();
    }
    */
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

  // Set gameline pin to HIGH to notify Other's boards that the start button was pressed
  digitalWrite(GAMELINE_PIN,HIGH);
}

/***** debug screen for LCD display *****/
void debug(const LiquidCrystal_I2C& lcd, const Command& cmd){

  // clear LCD at the beginning of the function call
  lcd.clear();

  String checking_value = String(cmd.device_used) + "," + String(cmd.score);
  lcd.setCursor(0,0);
  lcd.print(checking_value);

  checking_value = String(cmd.yaw) + "," + String(cmd.roll) + "," + String(cmd.pitch);
  lcd.setCursor(0,1);
  lcd.print(checking_value);

}
   