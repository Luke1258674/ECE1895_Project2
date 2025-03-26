// connect to header file
#include "./Cockpit.h"

void cockpit_startup(LiquidCrystal_I2C lcd,Adafruit_SSD1306 pitch_display, Adafruit_SSD1306 roll_display, SoftwareSerial mySoftwareSerial,DFRobotDFPlayerMini myDFPlayer){

    /****** Set pins for LED shift register ******/
    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
    pinMode(DATA_PIN, OUTPUT);
    pinMode(CLEAR_PIN, OUTPUT);

    // clear shift register
    digitalWrite(CLEAR_PIN, LOW);
    digitalWrite(CLEAR_PIN, HIGH);

    // turn green LEDs on:
    // get ready to store shift register (stores at rising edge)
    digitalWrite(LATCH_PIN, LOW);

    // shift out the bits:
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 0x55 /* number to display */);

    // store shift register
    digitalWrite(LATCH_PIN, HIGH);

    // pause before next value:
    delay(500);

    /****** Connector Pin Initialization ******/
    pinMode(CONNECTOR_PIN, INPUT); 
    digitalWrite(CONNECTOR_PIN,LOW); // Disable internal pull up 

    /****** LCD Display Initialization ******/
    lcd.init();
    lcd.backlight();

    // Display press start
    showStartMenu(lcd);
    delay(500); 

    /****** OLED Display initialization ******/
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

    /****** DFPlayer Mini Initialization ******/
    // begin serial communication with baud rate 9600
    mySoftwareSerial.begin(9600);

    //Set serial communictaion time out 500ms
    myDFPlayer.setTimeOut(500); 

    // define initial values
    myDFPlayer.begin(mySoftwareSerial); // set serial port for myDFPlayer
    myDFPlayer.EQ(0); //Normal Equalization
    myDFPlayer.volume(15);  //Set volume value (0~30).

    // play "Press button to begin game" for 2 seconds 
    myDFPlayer.playFolder(1, 1);  
    delay(2000);
        

}