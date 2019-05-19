#include "menu.h"

#include "Adafruit_GFX.h"
#include "Adafruit_HT1632.h"

#define READ_BUTTON 12
  
void Menu::printIntroScreen(Adafruit_HT1632LEDMatrix matrix) {
  // Prints Welcome To:
  matrix.clearScreen();
  // draw some text!
  // size 1 == 8 pixels high
  matrix.setTextSize(1);    
  // this will light leds.
  matrix.setTextColor(1);
  matrix.setTextWrap(false);

  matrix.setCursor(3, 0); 
  matrix.print("Welcome");
  matrix.setCursor(18,8);
  matrix.print("To");
  matrix.writeScreen();

  delay(3000);
  
  // Blinks the words Tic Tac Toe three times
  printTicTacToe(matrix);
  printTicTacToe(matrix);
  printTicTacToe(matrix);
}

void Menu::displayEndMessage(String message, Adafruit_HT1632LEDMatrix matrix) {
  // Prints Welcome To:
  matrix.clearScreen();
  // draw some text!
  matrix.setTextSize(1);    // size 1 == 8 pixels high
  matrix.setTextColor(1);   // 'lit' LEDs
  matrix.setTextWrap(false);
  
  if (message == "Tie!") {
    matrix.setCursor(3, 0); 
    matrix.print("Tie!");
    matrix.writeScreen();
  }

  if (message == "Human wins!") {
    matrix.setCursor(0, 0); 
    matrix.print("Human");
    matrix.setCursor(0, 8); 
    matrix.print("wins!");
    matrix.writeScreen();
  }
	
	if (message ==  "AI wins!") {
	  matrix.setCursor(0, 0); 
    matrix.print("AI");
    matrix.setCursor(0, 8); 
    matrix.print("wins!");
    matrix.writeScreen();
	}
 
  if (message == "Player 1 wins!") {
	  matrix.setCursor(0, 0); 
    matrix.print("Player 1");
    matrix.setCursor(0, 8); 
    matrix.print("wins!");
    matrix.writeScreen();
	}

  if (message == "Player 2 wins!") {
     matrix.setCursor(0, 0); 
    matrix.print("Player 2");
    matrix.setCursor(0, 8); 
    matrix.print("wins!");
    matrix.writeScreen();
  }

  delay(3000);
  matrix.clearScreen();
}

void Menu::printTicTacToe(Adafruit_HT1632LEDMatrix matrix) {
  // draw some text!
  matrix.clearScreen();
  matrix.setTextSize(1.5);  
  matrix.setTextColor(1); 
  matrix.setTextWrap(true);
  matrix.setCursor(3, 0);
  matrix.print("Tic Tac\n");
  matrix.setCursor(14,8);
  matrix.print("Toe!");
  matrix.writeScreen();
  delay(1000);
  matrix.clearScreen();
  delay(500);
}

String Menu::chooseMode(Joystick joystick, Adafruit_HT1632LEDMatrix matrix) {
  matrix.clearScreen();
  matrix.setTextSize(0.5);
  matrix.setTextColor(1);
  matrix.setTextWrap(false);
  matrix.setCursor(6,0);
  matrix.print("Choose");
  matrix.setCursor(10,8);
  matrix.print("Mode!");
  matrix.writeScreen();
  delay(1500);
  matrix.clearScreen();

  matrix.setCursor(6, 0);
  matrix.print("Single");
  matrix.setCursor(10,8);
  matrix.print("Multi");
  matrix.writeScreen();
  return chooseGameModeOption(joystick, matrix);
}

void Menu::blinkGameOption(String typeOfMenu, int menuOptionNumber, Adafruit_HT1632LEDMatrix matrix) {
  if (typeOfMenu == "game_mode") {
    if (menuOptionNumber == 0) {
      matrix.clearScreen();
      matrix.setTextSize(0.5);
      matrix.setTextColor(1);
      matrix.setTextWrap(false);
      matrix.setCursor(10,8);
      matrix.print("Multi");
      matrix.writeScreen();
      delay(500);
      matrix.clearScreen();
      matrix.setTextSize(0.5);
      matrix.setTextColor(1); 
      matrix.setTextWrap(false);
      matrix.setCursor(6, 0);
      matrix.print("Single");
      matrix.setCursor(10,8);
      matrix.print("Multi");
      matrix.writeScreen();
      delay(500);
    }
    else if (menuOptionNumber == 1) {
      matrix.clearScreen();
      matrix.setTextSize(0.5);
      matrix.setTextColor(1); 
      matrix.setTextWrap(false);
      matrix.setCursor(6, 0); 
      matrix.print("Single");
      matrix.writeScreen();
      delay(500);
      matrix.clearScreen();
      matrix.setTextSize(0.5);
      matrix.setTextColor(1);  
      matrix.setTextWrap(false);
      matrix.setCursor(6, 0); 
      matrix.print("Single");
      matrix.setCursor(10,8);
      matrix.print("Multi");
      matrix.writeScreen();
      delay(500);
    }
  }
}

String Menu::chooseGameModeOption(Joystick joystick, Adafruit_HT1632LEDMatrix matrix) {
  int blinkNum = 0;
  while (true) {
    delay(100);
    String dir = joystick.isDirection();
    if (dir ==  "A: Nuetral, B: Down") {
      
      blinkNum = 1;
      Serial.print("down\n");
    }
    else if (dir ==  "A: Nuetral, B: Up") {
      blinkNum = 0;
      Serial.print("up\n");
    }
    blinkGameOption("game_mode", blinkNum, matrix);
    if ( digitalRead(READ_BUTTON) == LOW ) {
      // If we have found a slot, then we win
      if (blinkNum == 0) {
        matrix.clearScreen();
        return "single";
      } 
      else if (blinkNum == 1) {
        matrix.clearScreen();
        return "multi";
      }
    }
  }
}
  
