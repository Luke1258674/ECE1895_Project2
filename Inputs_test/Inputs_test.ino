
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
unsigned long updateInterval = 5000;

// UART timing variables
unsigned long data_prev_update_time = 0;
unsigned long data_update_interval = 500;
bool newTxData = false; 

// values to use in the game
uint8_t device_used = 0; 
uint8_t previous_device_used = 0;
uint8_t score = 0;
bool user_action = false;
bool user_timeout = false;

// initialize struct
Command cmd;

void setup() {

  // initialize I/Os
  setup_GPIOpins(ledPins,buttonPins,ledStates,ledControlPins);

  // give sufficient time for cockpit board to setup
  delay(100);
}

void loop() {


  // select action
  if ((user_timeout == true) || (score == 100)){
    // game over 
    device_used = 255;

    // reset user_timeout flag
    user_timeout = false;

  }else{
    // randomly select an action 
    device_used = random(1,6);
  }

  // initialize values at 0 
  cmd.yaw = 0;
  cmd.roll = 0;
  cmd.pitch = 0;
  cmd.score = score;
  cmd.device_used = device_used;

  // select values based on device used
  if (device_used == 1){ cmd.roll = 45;            // turn left
  }else if (device_used == 2){ cmd.roll = -45;     // turn right
  }else if (device_used == 3){ cmd.pitch = -45;    // Ascend
  }else if (device_used == 4){ cmd.pitch = 45;     // Descend
  }else if (device_used == 5){ cmd.yaw = 45;       // flash the beacon
  }else{ // game over 
  }

  // wait for start button to be pressed and game line to be HIGH
  while (digitalRead(GAMELINE_PIN) == LOW){
    delay(10);
    // debug LED
    digitalWrite(ledControlPins[0], HIGH);
  }

  // send the struct
  //updateDataToSend(data_prev_update_time, data_update_interval, newTxData);
  newTxData = true;

  // initialize serial
  Serial.begin(9600);

  delay(100);

  transmitData(cmd,newTxData);

  delay(100);

  // end serial
  Serial.end();

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
    currentUpdateTime = millis();
    user_timeout = ((currentUpdateTime - prevUpdateTime) > updateInterval);
  }

  if (user_timeout == false){
    // add 1 to score
    score += 1;
    // reduce update intervale
    updateInterval -= 20;
  }

  // store previous input 
  previous_device_used = device_used;


}
