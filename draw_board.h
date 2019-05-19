/*
DrawBoard module

It draws all the game pieces and handles all the drawing
when it comes to the game.
*/

#ifndef DRAW_BOARD_H
#define DRAW_BOARD_H

#include "Adafruit_GFX.h"
#include "Adafruit_HT1632.h"


class DrawBoard {
  public:
  // Draws the game board.
  void initGameBoard(Adafruit_HT1632LEDMatrix matrix);

  // Blinks the piece as it is being selected
  void blinkBeforeSelection(char type, int pos, Adafruit_HT1632LEDMatrix matrix);
  
  // Write to a position 0...8 . The type == 'x' or 'o'. Draw is T means it
  // will draw the piece, if F it will erase at that position
  void writePosition(char type, int pos, bool draw, Adafruit_HT1632LEDMatrix matrix);
  
  private:
  // Game Board
  int x[3];
  int y[3];
  
  void drawO(int x, int y, bool draw, Adafruit_HT1632LEDMatrix matrix);

  void drawX(int x, int y, bool draw, Adafruit_HT1632LEDMatrix matrix);
  
  // Draws the game board lines.
  void drawVerticalLines(int x, int horizontalDistance, Adafruit_HT1632LEDMatrix matrix);

  void drawHorizontalLines(int x, int y, int verticalDistance, int horizontalDistance, Adafruit_HT1632LEDMatrix matrix);
  
};

#endif