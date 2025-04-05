
// Connect hearer files
#include "./User_input.h"

// Define pins
const int ledPins[] = {3, 4}; // LED output pins
const int buttonPins[] = {7, 8}; // Button input pins
bool ledStates[2] = {false, false}; // LED toggle states
const int ledControlPins[] = {5, 6, 9, 10}; // 4 LEDs for potentiometer control

// timing variables for sending frequency
unsigned long prevUpdateTime = 0;
unsigned long updateInterval = 500;
bool newTxData = false;

// Variable to control how many LEDs are lit
int ledsOn = 0;  

// values to use in the game
uint8_t device_used = 0; 
uint8_t score = 0;

// initialize struct
Command cmd;

void setup() {

  // initialize I/Os
  setup_GPIOpins(ledPins,buttonPins,ledStates,ledControlPins);

  // debug LED
  digitalWrite(ledControlPins[0], HIGH);
}

void loop() {
  // --- when game line is HIGH --- 

  // randomly select an action
  device_used = random(1,6);

  // initialize values at 0 
  cmd.yaw = 0;
  cmd.roll = 0;
  cmd.pitch = 0;
  //cmd.score = score;
  cmd.score = score;
  cmd.device_used = device_used;

  // select values based on device used
  if (device_used == 1){
    // turn left
    cmd.roll = 20;
  }else if (device_used == 2){
    // turn right
    cmd.roll = -20;
  }else if (device_used == 3){
    // climb
    cmd.pitch = -20;
  }else if (device_used == 4){
    // ascend
    cmd.pitch = 20;
  }else if (device_used == 5){
    // flash the beacon
    cmd.yaw = 20;
  }else{
    // not used
    cmd.yaw = -20;
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

  // flush the buffer
  Serial.flush();

  // end serial
  Serial.end();

  // debug
  digitalWrite(ledControlPins[1], HIGH);



  while(true);


    /*
    // --- Joystick Reading (your original code) ---
    int xRaw = analogRead(JOYSTICK_VRX); // Read X-axis
    int yRaw = analogRead(JOYSTICK_VRY); // Read Y-axis

    // Map the values from 0-1023 to -90 to 90
    int xMapped = map(xRaw, 0, 1023, -90, 90);
    int yMapped = map(yRaw, 0, 1023, -90, 90);

    // Read the Joystick button state (LOW means pressed)
    bool buttonPressed = (digitalRead(JOYSTICK_SW) == LOW);

    // --- Button 1 Reading ---
    if (digitalRead(buttonPins[0]) == LOW) {
      // Button 1 pressed (LOW state)
        ledStates[1] = !ledStates[1]; // Toggle LED 2
        digitalWrite(ledPins[1], ledStates[1] ? HIGH : LOW);

      // Confirm still pressed
      while (digitalRead(buttonPins[1]) == LOW);
    }

    // --- Button 2 Reading ---
    if (digitalRead(buttonPins[1]) == LOW) { 
        // Button 2 pressed (LOW state)
        ledStates[1] = !ledStates[1]; // Toggle LED 2
        digitalWrite(ledPins[1], ledStates[1] ? HIGH : LOW);
        
        // Confirm still pressed
        while (digitalRead(buttonPins[1]) == LOW);
    }

    // --- Potentiometer Reading ---
    int potValue = analogRead(POTENTIOMETER_PIN); // Read the potentiometer value (0 to 1023)

    // Map the potentiometer value to the number of LEDs to turn on (0-4 range)
    if (potValue<=50){
      ledsOn=0;
    }else if (potValue>50&&potValue<260){
      ledsOn=1;
    }else if (potValue>=260&&potValue<512){
      ledsOn=2;
    }else if (potValue>=512&&potValue<760){
      ledsOn=3;
    }else{
      ledsOn=4;
    }
    // Control the potentiometer-controlled LEDs based on the potentiometer value
        for (int i = 0; i < ledsOn; i++){
      digitalWrite(ledControlPins[i],HIGH);
    }

    for (int i = 4; i > ledsOn; i--){
      digitalWrite(ledControlPins[i],LOW);
    }

    delay(100);
    */
}
