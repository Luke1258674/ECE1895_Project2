// connect to header file
#include "./LCD_Display.h"

void showScoreAndTime(LiquidCrystal_I2C lcd, int score, int time) {
    // clear LCD at the beginning of the function call
    lcd.clear();

    // Reset integers if input is out of bounds: score > 100 or time > 60*99
    if ((score > 100) || (time > 60*99)){
        score = 0;
        time = 0;
    }
  
    // set cursor to 1st column and 1st row and print the message: "Score_______Time"
    lcd.setCursor(0,0);
    lcd.print("Score       Time");
  
    // Convert score to string
    
    // define string to store current time
    String currentScore;
  
    if (score < 10){
      currentScore = "0" + String(score) + " / 99";
    }else{
      currentScore = String(score) + " / 99";
    }
  
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
  
    // Add the score and time strings to gether
    String scoreAndTime = currentScore + "    " + currentTime;
  
    // Set cursor to 1nd column and 2nd row and print the message: "XX_/_99____XX:XX" 
    lcd.setCursor(0,1);
    lcd.print(scoreAndTime);
  }
  

  void showStartMenu(LiquidCrystal_I2C lcd){
    // clear LCD at the beginning of the function call
    lcd.clear();

    // Print the message: "Press Start to Take Off"
    lcd.setCursor(0,0);
    lcd.print("PRESS START TO");
    lcd.setCursor(0,1);
    lcd.print("TAKE OFF");
  }
  

  void showGameOver(LiquidCrystal_I2C lcd, int score, int time){
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