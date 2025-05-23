#include "Arduino.h"

#include "./User_input.h"

void setup_GPIOpins(const int ledPins[], const int buttonPins[], bool ledStates[], const int ledControlPins[]){
    // Setup Joystick Pins
    pinMode(JOYSTICK_VRX, INPUT); // X-axis
    pinMode(JOYSTICK_VRY, INPUT); // Y-axis
    pinMode(JOYSTICK_SW, INPUT_PULLUP); // Button input with internal pull-up resistor

    // potentiometer
    pinMode(POTENTIOMETER_PIN, INPUT); // Potentiometer 
    
    // Setup LED Output Pins
    for (int i = 0; i < 2; i++) {
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW); // Start with LEDs off
    }

    // Setup Button Pins to input 
    for (int i = 0; i < 2; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP); // Use internal pull-up resistor
    }

    // Setup Potentiometer LED Pins
    for (int i = 0; i < 2; i++) {
        pinMode(ledControlPins[i], OUTPUT); // Set the LED pins as output
        digitalWrite(ledControlPins[i], HIGH); // Start with LEDs off
    }
    for (int k = 2; k < 4; k++)
        {
        pinMode(ledControlPins[k], OUTPUT); // Set the LED pins as output
        digitalWrite(ledControlPins[k], LOW); // Start with LEDs off
        }

    // set up game line pin to input
    pinMode(GAMELINE_PIN,INPUT_PULLUP);
    
}

void updateDataToSend(unsigned long& prevUpdateTime, unsigned long updateInterval, bool &newTxData){
  if ((millis() - prevUpdateTime) >=  updateInterval){
    prevUpdateTime = millis();
    // ensure message has been sent
    if (newTxData == false){

      newTxData == true;
    }
  }
}

void transmitData(const Command& cmd, bool &newTxData){

  delay(100);

  // size of transmit data 
  const byte startMarker = 23;
  const byte cmdDataLen = sizeof(cmd);

  if (newTxData == true){
    Serial.write(startMarker);

    Serial.write((byte*) &cmd, cmdDataLen);

    newTxData = false;
  }

  delay(100);
}

void turn_left_action(bool& user_action, const int ledControlPins[], int& currentrotory, int& currentY, bool& user_timeout,const int buttonPins[], int& ledsOn){
  int NumberOfLEDsOnCurrently=ledsOn;
    // ckcking the value of joystick in case it was used
  int yRaw_check = analogRead(JOYSTICK_VRY); // Read Y-axis
  int yMapped_check = map(yRaw_check, 0, 1023, -90, 90);
  
  // turn left --- Potentiometer Reading ---
  int pot_value = analogRead(POTENTIOMETER_PIN); // Read the potentiometer value (0 to 1023)
  
  int pot_value_mapped = map(pot_value, 0, 1023, 0, 270); // map to 0 to 270 degrees
  // curent rotary value used to check if incorrect action was taken
  currentrotory=pot_value_mapped;
  // Variable to control how many LEDs are lit
  

  // Map the potentiometer value to the number of LEDs to turn on (0-4 range)
  if (pot_value_mapped<=45){ ledsOn=0;
  }else if (pot_value_mapped<=90){ ledsOn=1;
  }else if (pot_value_mapped<=180){ ledsOn=2;
  }else if (pot_value_mapped<=225){ ledsOn=3;
  }else{ ledsOn=4; 
  }
  // checking if incorrect actions were taken
  if (yMapped_check < -20 || yMapped_check > 20){
    user_timeout = true;
  }
  else if (digitalRead(buttonPins[0]) == LOW){
    user_timeout = true;
  }
  else if (pot_value_mapped >= 225){
    user_timeout = true;
  }
  
  // Control the potentiometer-controlled LEDs based on the potentiometer value
  // along with checking only one LED was turned off when rotating right
  if(pot_value_mapped<=180){
    for (int i = 0; i < ledsOn; i++){
      digitalWrite(ledControlPins[i],HIGH);
    }
    
    for (int p=ledsOn; p<4; p++){
      digitalWrite(ledControlPins[p],LOW);
    }
  user_action = true;
  }else {
    user_action = false;
  }
  delay(100);
}

void turn_right_action(bool& user_action, const int ledControlPins[],int& currentrotory, int& currentY, bool& user_timeout,const int buttonPins[], int& ledsOn){
  int NumberOfLEDsOnCurrently=ledsOn;
  // checking joystick in case it was used
  int yRaw_check = analogRead(JOYSTICK_VRY); // Read Y-axis
  int yMapped_check = map(yRaw_check, 0, 1023, -90, 90);
    
  int pot_value = analogRead(POTENTIOMETER_PIN); // Read the potentiometer value (0 to 1023)
  int pot_value_mapped = map(pot_value, 0, 1023, 0, 270); // map to 0 to 270 degrees
  // using this for incorrect input ckecking  
  currentrotory=pot_value_mapped;
    
  
    // Map the potentiometer value to the number of LEDs to turn on (0-4 range)
    if (pot_value_mapped<=45){ ledsOn=0;
    }else if (pot_value_mapped<=90){ ledsOn=1;
    }else if (pot_value_mapped<=180){ ledsOn=2;
    }else if (pot_value_mapped<=225){ ledsOn=3;
    }else{ ledsOn=4; 
    }

  // checking for incorrect action
  if (yMapped_check < -20 || yMapped_check > 20){
    user_timeout = true;
  }
  else if (digitalRead(buttonPins[0]) == LOW){
    user_timeout = true;
  }
  else if (pot_value_mapped <= 45){
    user_timeout = true;
  }


    if(pot_value_mapped>180){
    for (int i = 0; i < ledsOn; i++){
      digitalWrite(ledControlPins[i],HIGH);
    }
    
    for (int p=ledsOn; p<4; p++){
      digitalWrite(ledControlPins[p],LOW);
    }
  user_action = true;
 else {
    user_action = false;
  }
  delay(100);   
}

void ascend_action(bool& user_action, int& currentrotory, int& currentY, bool& user_timeout,const int buttonPins[], int& ledsOn){
    // --- Joystick Reading (your original code) ---
    int xRaw = analogRead(JOYSTICK_VRX); // Read X-axis
    int yRaw = analogRead(JOYSTICK_VRY); // Read Y-axis

    // Map the values from 0-1023 to -90 to 90
    int xMapped = map(xRaw, 0, 1023, -90, 90);
    int yMapped = map(yRaw, 0, 1023, -90, 90);
  // in case rotary dial was used ckecking value
  int checking_value = analogRead(POTENTIOMETER_PIN); // Read the potentiometer value (0 to 1023)
  int checking_value_mapped = map(checking_value, 0, 1023, 0, 270); // map to 0 to 270 degrees
  // running ckecks if the incorrect action was taken
  // Map the potentiometer value to the number of LEDs to turn on (0-4 range)
    int errorLedsOn;
    if (checking_value_mapped<=45){ errorLedsOn=0;
    }else if (checking_value_mapped<=90){ errorLedsOn=1;
    }else if (checking_value_mapped<=180){ errorLedsOn=2;
    }else if (checking_value_mapped<=225){ errorLedsOn=3;
    }else{ errorLedsOn=4; 
    }
  if (errorLedsOn!= ledsOn)
  {
    user_timeout = true;
  }
  else if (yMapped >= 1)
  {
    user_timeout = true;
  }
  else if (digitalRead(buttonPins[0]) == LOW)
  {
    user_timeout = true;
  }
    // variable for incorrect action check
    currentY=yMapped;
    // check user action (if user_action is true, exit while loop)
    user_action = (yMapped <= -45);

    delay(100);
}

void descend_action(bool& user_action, int& currentrotory, int& currentY, bool& user_timeout,const int buttonPins[], int& ledsOn){
    // --- Joystick Reading (your original code) ---
  // checking rotary dial if it was used when not prompted to
  int checking_value = analogRead(POTENTIOMETER_PIN); // Read the potentiometer value (0 to 1023)
  int checking_value_mapped = map(checking_value, 0, 1023, 0, 270); // map to 0 to 270 degrees

    
  int xRaw = analogRead(JOYSTICK_VRX); // Read X-axis
  int yRaw = analogRead(JOYSTICK_VRY); // Read Y-axis

    // Map the values from 0-1023 to -90 to 90
    int xMapped = map(xRaw, 0, 1023, -90, 90);
    int yMapped = map(yRaw, 0, 1023, -90, 90);

    
  // checking there is no incorrect action
  int errorLedsOn;
    if (checking_value_mapped<=45){ errorLedsOn=0;
    }else if (checking_value_mapped<=90){ errorLedsOn=1;
    }else if (checking_value_mapped<=180){ errorLedsOn=2;
    }else if (checking_value_mapped<=225){ errorLedsOn=3;
    }else{ errorLedsOn=4; 
    }
  if (errorLedsOn!=ledsOn)
  {
    user_timeout = true;
  }
  else if (yMapped <=-1)
  {
    user_timeout = true;
  }
  else if (digitalRead(buttonPins[0]) == LOW)
  {
    user_timeout = true;
  }

    // variable used for incorrect action check
    currentY=yMapped;
    
    // check user action (if user_action is true, exit while loop)
    user_action = (yMapped >= 45);

    delay(100);
}

void press_button_action(bool& user_action, const int ledPins[], bool ledStates[],const int buttonPins[], int& currentrotory, int& currentY, bool& user_timeout, int& ledsOn){
  // --- Button 1 Reading ---
  // checking potentiometer value and joystick value in case they were used instead of button
  int checking_value = analogRead(POTENTIOMETER_PIN); // Read the potentiometer value (0 to 1023)
  int checking_value_mapped = map(checking_value, 0, 1023, 0, 270); // map to 0 to 270 degrees
  int yRaw_check = analogRead(JOYSTICK_VRY); // Read Y-axis
  int yMapped_check = map(yRaw_check, 0, 1023, -90, 90);

  // checking if incorrect action was taken
  int errorLedsOn;
    if (checking_value_mapped<=45){ errorLedsOn=0;
    }else if (checking_value_mapped<=90){ errorLedsOn=1;
    }else if (checking_value_mapped<=180){ errorLedsOn=2;
    }else if (checking_value_mapped<=225){ errorLedsOn=3;
    }else{ errorLedsOn=4; 
    }
  if (errorLedsOn!=ledsOn)
  {
    user_timeout = true;
  }
  if (yMapped_check < -10 || yMapped_check > 10)
  {
    user_timeout = true;
  }
  

  if (digitalRead(buttonPins[0]) == LOW) {
  // Button 1 pressed (LOW state)
    ledStates[0] = !ledStates[0]; // Toggle LED 2
    digitalWrite(ledPins[0], ledStates[0] ? HIGH : LOW);
    ledStates[1] = !ledStates[1]; // Toggle LED 2
    digitalWrite(ledPins[1], ledStates[1] ? HIGH : LOW);
  // Confirm still pressed
  while (digitalRead(buttonPins[0]) == LOW);

  // update user action (if user_action is true, exit while loop)
  user_action = true;    
  }
  // possibly adding a second toggle button
  // --- Button 2 Reading ---
  if (digitalRead(buttonPins[1]) == LOW) { 
    // Button 2 pressed (LOW state)
    ledStates[1] = !ledStates[1]; // Toggle LED 2
    digitalWrite(ledPins[1], ledStates[1] ? HIGH : LOW);
    
    // Confirm still pressed
    while (digitalRead(buttonPins[1]) == LOW);

    // update user action (if user_action is true, exit while loop)
    user_action = true;
  }

  delay(100);
}


