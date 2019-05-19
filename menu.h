/*
Menu module

Displays all the game menus, the option to choose things, and pop up messages.
*/

#ifndef MENU_H
#define MENU_H

#include "Arduino.h"
#include "joystick.h"

#include "Adafruit_GFX.h"
#include "Adafruit_HT1632.h"

// GAME MENUS *******************
class Menu {
  
  public:
  // Prints Welcome message.
  void printIntroScreen(Adafruit_HT1632LEDMatrix matrix);
 
  // Prints end of game message. 
  void displayEndMessage(String message, Adafruit_HT1632LEDMatrix matrix);

  // Displays the meny and chooses the game mode between single or multi  
  String chooseMode(Joystick joystick, Adafruit_HT1632LEDMatrix matrix);

  
  
  private:
  // Used in printIntroScreen function
  void printTicTacToe(Adafruit_HT1632LEDMatrix matrix);
  
  // Used in chooseMode
  void blinkGameOption(String typeOfMenu, int menuOptionNumber, Adafruit_HT1632LEDMatrix matrix);

  // Used in chooseMode
  String chooseGameModeOption(Joystick joystick, Adafruit_HT1632LEDMatrix matrix);
};

#endif