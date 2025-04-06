#include "./OLED_display.h"

void displayPitchIndicator_static(Adafruit_SSD1306 display){

    // clear screen 
    display.clearDisplay();
    
    // define middle point
    uint16_t xt0 = display.width()/2;
    uint16_t yt0 = display.height()/2;

    // display triangle in the middle
    display.fillTriangle(xt0+15,yt0+15,xt0,yt0,xt0-15,yt0+15,SSD1306_WHITE);

    // define points to plot lines
    uint16_t x0 = display.width()/2-46;
    uint16_t y0 = display.height()/2;
    uint16_t x1 = display.width()/2+46;

    // define display text settings
    display.setTextSize(1); // set text size to 1 (default), 2 larger, 3 largest
    display.setTextColor(SSD1306_WHITE); // set text color to white
    display.cp437(true);         // Use full 256 char 'Code Page 437' font
    int bits_per_char = 6; // 6 bits per character is needed for the display

    // display five lines for each 5 degree pitch
    for (uint16_t i = 0; i <= 2; i++){
        int offset_top = (i * display.height()/4)+1;
        int offset_bottom = (i * display.height()/4)-1;

        // display lines for 0, 5, and 10 degrees
        display.drawLine(x0,y0+offset_top,x1,y0+offset_top,SSD1306_WHITE);

        if (i !=0){
            display.drawLine(x0,y0-offset_bottom,x1,y0-offset_bottom,SSD1306_WHITE);
        }

        // give 3 characters of space (6 per word) when displaying values over 10 degrees 
        if (i*5 >= 10){
            // display digits on the left 
            display.setCursor(x0-bits_per_char*3, y0-offset_bottom-4);
            display.print((int)i*5);

            // display digits on the right
            display.setCursor(x1, y0-offset_bottom-4);
            display.print((int)i*5);

            if (i != 0){
                // display digits on the left 
                display.setCursor(x0-bits_per_char*3, y0+offset_top-4);
                display.print((int)-i*5);

                // display digits on the right
                display.setCursor(x1, y0+offset_top-4);
                display.print((int)-i*5);
            }
        }else{
        // give 1 character of space (6 per word) when displaying values over 10 degrees 
            // display digits on the left 
            display.setCursor(x0-bits_per_char*2, y0-offset_bottom-4);
            display.print((int)i*5);

            // display digits on the right
            display.setCursor(x1+bits_per_char, y0-offset_bottom-4);
            display.print((int)i*5);

            if (i != 0){
                // display digits on the left 
                display.setCursor(x0-bits_per_char*3, y0+offset_top-4);
                display.print((int)-i*5);

                // display digits on the right
                display.setCursor(x1, y0+offset_top-4);
                display.print((int)-i*5);
            }
        }
    }

    // Show the display buffer on the screen
    display.display();
    delay(100);
}

void displayRollIndicator_static(Adafruit_SSD1306 display){
      // clear screen 
    display.clearDisplay();
    
    // define middle point
    uint16_t x0 = display.width()/2;
    uint16_t y0 = display.height()/2;

    // define the radius
    uint16_t radius = 10;

    // define points used to make lines
    uint16_t y_rudder_top = y0-25;
    uint16_t x_elevator_left = x0-20;
    uint16_t x_elevator_right = x0+20;
    uint16_t y_elevator = y0-10;
    uint16_t x_wing_left = x0-46;
    uint16_t x_wing_right = x0 +46;

    // display the aircraft body
    display.fillCircle(x0, y0, radius, SSD1306_WHITE);

    // display a wing
    display.drawLine(x_wing_left,y0,x_wing_right,y0, SSD1306_WHITE);
    display.drawLine(x_wing_left+1,y0+1,x_wing_right-1,y0+1, SSD1306_WHITE);

    // display a rudder
    display.drawLine(x0,y0,x0,y_rudder_top, SSD1306_WHITE);

    // display the elevator
    display.drawLine(x_elevator_left,y_elevator,x_elevator_right,y_elevator, SSD1306_WHITE);

    // display the units at 0 degrees
    display.drawLine(0,y0,10,y0, SSD1306_WHITE);
    display.drawLine(display.width()-10,y0,display.width(),y0, SSD1306_WHITE);
    
    // display the units at 10 degrees
    display.drawLine(0,y0+20,10,y0+15, SSD1306_WHITE);
    display.drawLine(display.width()-10,y0+15,display.width(),y0+20, SSD1306_WHITE);

    // Show the display buffer on the screen
    display.display();
    delay(100);

}

void displayPitchIndicator_transient(Adafruit_SSD1306 display,int pitch){

    // clear screen 
    display.clearDisplay();

    // define middle point
    uint16_t xt0 = display.width()/2;
    uint16_t yt0 = display.height()/2;

    // display triangle in the middle
    display.fillTriangle(xt0+15,yt0+15,xt0,yt0,xt0-15,yt0+15,SSD1306_WHITE);

    // define points to plot lines
    uint16_t x0 = display.width()/2-46;
    uint16_t y0 = display.height()/2;
    uint16_t x1 = display.width()/2+46;

    // define display text settings
    display.setTextSize(1); // set text size to 1 (default), 2 larger, 3 largest
    display.setTextColor(SSD1306_WHITE); // set text color to white
    display.cp437(true);         // Use full 256 char 'Code Page 437' font
    int bits_per_char = 6; // 6 bits per character is needed for the display

    // move the display lines based on pitch degree
    for (uint16_t i = 0; i <= 9; i++){
        int offset_top = (i * display.height()/4)+1+pitch*3;
        int offset_bottom = (i * display.height()/4)-1-pitch*3;

        // display lines for 0, 5, and 10 degrees
        display.drawLine(x0,y0+offset_top,x1,y0+offset_top,SSD1306_WHITE);

        if (i !=0){
            display.drawLine(x0,y0-offset_bottom,x1,y0-offset_bottom,SSD1306_WHITE);
        }

        // give 3 characters of space (6 per word) when displaying values over 10 degrees 
        if (i*5 >= 10){
            // display digits on the left 
            display.setCursor(x0-bits_per_char*3, y0-offset_bottom-4);
            display.print((int)i*5);

            // display digits on the right
            display.setCursor(x1, y0-offset_bottom-4);
            display.print((int)i*5);

            if (i != 0){
                // display digits on the left 
                display.setCursor(x0-bits_per_char*3, y0+offset_top-4);
                display.print((int)-i*5);

                // display digits on the right
                display.setCursor(x1, y0+offset_top-4);
                display.print((int)-i*5);
            }
        }else{
        // give 1 character of space (6 per word) when displaying values over 10 degrees 
            // display digits on the left 
            display.setCursor(x0-bits_per_char*2, y0-offset_bottom-4);
            display.print((int)i*5);

            // display digits on the right
            display.setCursor(x1+bits_per_char, y0-offset_bottom-4);
            display.print((int)i*5);

            if (i != 0){
                // display digits on the left 
                display.setCursor(x0-bits_per_char*3, y0+offset_top-4);
                display.print((int)-i*5);

                // display digits on the right
                display.setCursor(x1, y0+offset_top-4);
                display.print((int)-i*5);
            }
        }
    }

    // Show the display buffer on the screen
    display.display();
    delay(200);

}

void displayRollIndicator_transient(Adafruit_SSD1306 display, int roll){

  // clear screen 
  display.clearDisplay();
  
  // define middle point
  uint16_t x0 = display.width()/2;
  uint16_t y0 = display.height()/2;

  // define the radius
  uint16_t radius = 10;

  // display the aircraft body
  display.fillCircle(x0, y0, radius, SSD1306_WHITE);

  // display the units at 0 degrees
  display.drawLine(0,y0,10,y0, SSD1306_WHITE);
  display.drawLine(display.width()-10,y0,display.width(),y0, SSD1306_WHITE);
  
  // display the units at 10 degrees
  display.drawLine(0,y0+20,10,y0+15, SSD1306_WHITE);
  display.drawLine(display.width()-10,y0+15,display.width(),y0+20, SSD1306_WHITE);

  // move the wing, rudder, and elevator based on the roll angle
  double sine_value = sin((double)roll/180*PI);
  double cosine_value = cos((double)roll/180*PI);
  
  // display a wing
  uint16_t wing_length = 46;
  uint16_t x_wing_right = x0 + wing_length*cosine_value;
  uint16_t x_wing_left = x0 - wing_length*cosine_value;
  uint16_t y_wing_right = y0 + wing_length*sine_value; 
  uint16_t y_wing_left =  y0 - wing_length*sine_value;  
  // change the angle of the wing based on the roll angle
  display.drawLine(x_wing_left,y_wing_left,x_wing_right,y_wing_right, SSD1306_WHITE);
  display.drawLine(x_wing_left+1,y_wing_left+1,x_wing_right-1,y_wing_right+1, SSD1306_WHITE);

  // display a rudder
  uint16_t rudder_height = 25;
  uint16_t x_rudder_top = x0 + rudder_height*sine_value;
  uint16_t y_rudder_width = y0 - rudder_height*cosine_value; 
  // change the height of the rudder based on the roll angle
  display.drawLine(x0,y0,x_rudder_top,y_rudder_width, SSD1306_WHITE);

  // display the elevator
  uint16_t elevator_width = 20;
  uint16_t x_elevator_right = x0 + elevator_width*cosine_value;
  uint16_t x_elevator_left = x0 - elevator_width*cosine_value;
  uint16_t y_elevator_right = y0 - 10 + elevator_width*sine_value; 
  uint16_t y_elevator_left =  y0 - 10 - elevator_width*sine_value;
  // change the angle of the elevator based on the roll angle
  display.drawLine(x_elevator_left,y_elevator_left,x_elevator_right,y_elevator_right, SSD1306_WHITE);

  // Show the display buffer on the screen
  display.display();
  delay(200);

}

