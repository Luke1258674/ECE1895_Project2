
// Connect hearer files
#include "./User_input.h"

// Define pins
const int ledPins[] = {3, 4}; // LED output pins
const int buttonPins[] = {7, 8}; // Button input pins
bool ledStates[2] = {false, false}; // LED toggle states
const int ledControlPins[] = {5, 6, 9, 10}; // 4 LEDs for potentiometer control

// timing variables
unsigned long prevUpdateTime = 0;
unsigned long currentUpdateTime = 0;
unsigned long updateInterval = 500;
bool newTxData = false; 

// values to use in the game
uint8_t device_used = 0; 
uint8_t score = 0;
bool user_action = false;
bool user_timeout = false;

// initialize struct
Command cmd;

void setup() {

  // initialize I/Os
  setup_GPIOpins(ledPins,buttonPins,ledStates,ledControlPins);
}

void loop() {
  // randomly select an action
  // device_used = random(1,6);
  device_used = 1;

  // initialize values at 0 
  cmd.yaw = 0;
  cmd.roll = 0;
  cmd.pitch = 0;
  //cmd.score = score;
  cmd.score = score;
  cmd.device_used = device_used;

  // select values based on device used
  if (device_used == 1){ cmd.roll = 20;            // turn left
  }else if (device_used == 2){ cmd.roll = -20;     // turn right
  }else if (device_used == 3){ cmd.pitch = -20;    // Ascend
  }else if (device_used == 4){ cmd.pitch = 20;     // Descend
  }else if (device_used == 5){ cmd.yaw = 20;       // flash the beacon
  }else{ // game over 
  }

  delay(100);

  // wait for start button to be pressed and game line to be HIGH
  while (digitalRead(GAMELINE_PIN) == LOW){
    delay(10);
    // debug LED
    digitalWrite(ledControlPins[0], HIGH);
  }

  delay(100);

  // initialize serial
  Serial.begin(9600);

  // send the struct
  newTxData = true;
  transmitData(cmd,newTxData);

  // end serial
  Serial.end();

  // debug
  digitalWrite(ledControlPins[1], HIGH);

  // delay
  delay(100);

  // Start timer and initialize game
  prevUpdateTime = millis();
  user_action = false;

  // wait for user input 
  while ((user_action == false) && (user_timeout == false)) {

  if (device_used == 1){
    // read potetiometer during turn left action and update user_action flag
    turn_left_action(user_action, ledControlPins);

  }else if (device_used == 2){
    // read potetiometer during turn right action and update user_action flag
    turn_right_action(user_action,ledControlPins);

  }else if (device_used == 3){
    // read joystick during ascend action and update user_action flag
    ascend_action(user_action);

  }else if (device_used == 4){
    // read joystick during descend action and update user_action flag
    descend_action(user_action);

  }else if (device_used == 5){
    // read button during flash the beacon action and update user_action flag
    press_button_action(user_action,ledPins,ledStates, buttonPins);
  }
    // check time (if user_timeout is true, exist while loop)
    delay(100);
    currentUpdateTime = millis();
    user_timeout = (currentUpdateTime - prevUpdateTime) > updateInterval;
  }

  if (user_timeout == false){
    // add 1 to score
    score += 1;
  }else{
    // reset score after user_timeout is true and breaking out of loop
    score = 0;
  }

  // debug
  digitalWrite(ledControlPins[2], HIGH);

  // delay
  delay(100);

  // debug (clear all)
  for (int i = 0; i < 4;i++){
    digitalWrite(ledControlPins[i], LOW);
  }

  // delay
  delay(100);



}
