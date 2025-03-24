const int ledPins[] = {5, 6}; // LED output pins
const int buttonPins[] = {7, 8}; // Button input pins
bool ledStates[2] = {false, false}; // LED toggle states

// Potentiometer and 4 LEDs

//const int ledControlPins[] = {9, 10, 3, 4}; // 4 LEDs for potentiometer control
//int ledsOn = 0;  // Variable to control how many LEDs are lit

void setup() {
    Serial.begin(9600);

    // Joystick Pins (your original code)
    pinMode(A0, INPUT); // X-axis
    pinMode(A1, INPUT); // Y-axis
    pinMode(2, INPUT_PULLUP); // Button input with internal pull-up resistor
    pinMode(A2, INPUT);
    // LED Output Pins
    for (int i = 0; i < 2; i++) {
        pinMode(ledPins[i], OUTPUT);
        digitalWrite(ledPins[i], LOW); // Start with LEDs off
    }

    // Button Pins
    for (int i = 0; i < 2; i++) {
        pinMode(buttonPins[i], INPUT_PULLUP); // Use internal pull-up resistor
    }

    // Potentiometer-controlled LEDs
    /*for (int i = 0; i < 4; i++) {
        pinMode(ledControlPins[i], OUTPUT); // Set the LED pins as output
        digitalWrite(ledControlPins[i], LOW); // Start with LEDs off
    }
    */
}

void loop() {
    // --- Joystick Reading (your original code) ---
    int xRaw = analogRead(A0); // Read X-axis
    int yRaw = analogRead(A1); // Read Y-axis

    // Map the values from 0-1023 to -512 to 512
    int xMapped = map(xRaw, 0, 1023, -512, 512);
    int yMapped = map(yRaw, 0, 1023, -512, 512);

    // Read the button state (LOW means pressed)
    bool buttonPressed = digitalRead(2) == LOW;

    // Print joystick values to serial monitor
    Serial.write(xRaw);
    delay(100); // Small delay for readability

    // --- Button 1 Reading ---
    if (digitalRead(buttonPins[0]) == LOW) { // Button 1 pressed (LOW state)
      
        if (digitalRead(buttonPins[0]) == LOW) { // Confirm still pressed
            ledStates[0] = !ledStates[0]; // Toggle LED 1
            digitalWrite(ledPins[0], ledStates[0] ? HIGH : LOW);
        }
        while (digitalRead(buttonPins[0]) == LOW);
    }

    // --- Button 2 Reading ---
    if (digitalRead(buttonPins[1]) == LOW) { // Button 2 pressed (LOW state)
        
        if (digitalRead(buttonPins[1]) == LOW) { // Confirm still pressed
            ledStates[1] = !ledStates[1]; // Toggle LED 2
            digitalWrite(ledPins[1], ledStates[1] ? HIGH : LOW);
        }
        while (digitalRead(buttonPins[1]) == LOW);
    }
/*
    // --- Potentiometer Reading ---
    int potValue = analogRead(A2); // Read the potentiometer value (0 to 1023)

    // Map the potentiometer value to the number of LEDs to turn on (0-4 range)
    if (potValue<=50)
    {
      ledsOn=0;
    }
    if (potValue>50&&potValue<260)
    {
      ledsOn=1;
    }
    if (potValue>=260&&potValue<512)
    {
      ledsOn=2;
    }
    if (potValue>=512&&potValue<760)
    {
      ledsOn=3;
    }
    if (potValue>=760)
    {
      ledsOn=4;
    }
    // Control the potentiometer-controlled LEDs based on the potentiometer value
    for (int i = 0; i < 4; i++) {
        if (i < ledsOn) {
            digitalWrite(ledControlPins[i], HIGH);  // Turn on LED
        } else {
            digitalWrite(ledControlPins[i], LOW);   // Turn off LED
        }
    }
*/
    delay(100); // Small delay for stability
}
