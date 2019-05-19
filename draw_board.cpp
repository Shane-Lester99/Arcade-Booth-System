#include "draw_board.h"

void DrawBoard::initGameBoard(Adafruit_HT1632LEDMatrix matrix) {
  x[0] = 3 + 12;
  x[1] = 11 + 12;
  x[2] = 18 + 12;
  y[0] = 1;
  y[1] = 7;
  y[2] = 13;
  
  // This willl draw the gameboard. The numbers are hardware specific and unintuitive.
  // They were found by trial and error
  drawVerticalLines(8 + 12, 8, matrix);
  drawHorizontalLines(2 + 12, 5, 19, 6, matrix);
}

void DrawBoard::blinkBeforeSelection(char type, int pos, Adafruit_HT1632LEDMatrix matrix) {
  writePosition(type, pos, true, matrix);
  delay(500);
  writePosition(type, pos, false, matrix);
  delay(500);
}

void DrawBoard::writePosition(char type, int pos, bool draw, Adafruit_HT1632LEDMatrix matrix) {
  if (pos == 0) {
    if (type == 'o') {
      drawO(x[0], y[0], draw, matrix);
    } else {
      drawX(x[0], y[0], draw, matrix);
    }
  } else if (pos == 1) {
    if (type == 'o') {
      drawO(x[1], y[0], draw, matrix);
    } else {
      drawX(x[1], y[0], draw, matrix);
    }
  }
   else if (pos == 2) {
     if (type == 'o') {
      drawO(x[2], y[0], draw, matrix);
    } else {
      drawX(x[2], y[0], draw, matrix);
    } 
  } else if (pos == 3) {
    if (type == 'o') {
      drawO(x[0], y[1], draw, matrix);
    } else {
      drawX(x[0], y[1], draw, matrix);
    }
  } 
  else if (pos == 4) {
    if (type == 'o') {
      drawO(x[1], y[1], draw, matrix);
    } else {
      drawX(x[1], y[1], draw, matrix);
    }
    
  } 
  else if (pos == 5) {
     if (type == 'o') {
      drawO(x[2], y[1], draw, matrix);
    } else {
      drawX(x[2], y[1], draw, matrix);
    }
  }
  else if (pos == 6) {
    if (type == 'o') {
      drawO(x[0], y[2], draw, matrix);
    } else {
      drawX(x[0], y[2], draw, matrix);
    }
  
  }
  else if (pos == 7) {
     if (type == 'o') {
      drawO(x[1], y[2], draw, matrix);
    } else {
      drawX(x[1], y[2], draw, matrix);
    }
  } 
  
   else if (pos == 8) {
     if (type == 'o') {
      drawO(x[2], y[2], draw, matrix);
    } else {
      drawX(x[2], y[2], draw, matrix);
    }
  }
}
  
void DrawBoard::drawO(int x, int y, bool draw, Adafruit_HT1632LEDMatrix matrix) {
  if (draw) {
    matrix.drawPixel(x + 1, y, 1);
    matrix.drawPixel(x, y + 1, 1);
    matrix.drawPixel(x + 2, y + 1, 1);
    matrix.drawPixel(x + 1, y + 2, 1);
    matrix.writeScreen();
  } else {
    matrix.clrPixel(x + 1, y);
    matrix.clrPixel(x, y + 1);
    matrix.clrPixel(x + 2, y + 1);
    matrix.clrPixel(x + 1, y + 2);
    matrix.writeScreen();
  }
  
}

void DrawBoard::drawX(int x, int y, bool draw, Adafruit_HT1632LEDMatrix matrix) {
  if (draw) {
    matrix.drawPixel(x, y, 1);
    matrix.drawPixel(x + 1, y + 1, 1);
    matrix.drawPixel(x + 2, y, 1);
    matrix.drawPixel(x, y + 2, 1);
    matrix.drawPixel(x + 2, y + 2, 1);
    matrix.writeScreen();
  } else {
    matrix.clrPixel(x, y);
    matrix.clrPixel(x + 1, y + 1);
    matrix.clrPixel(x + 2, y);
    matrix.clrPixel(x, y + 2);
    matrix.clrPixel(x + 2, y + 2);
    matrix.writeScreen();
  }
}

void DrawBoard::drawVerticalLines(int x, int horizontalDistance, Adafruit_HT1632LEDMatrix matrix) {
  // Vertical Lines of Board
  matrix.drawLine(x, 0, x, matrix.height() - 1 , 1);
  matrix.drawLine(x+horizontalDistance,0, x + horizontalDistance, matrix.height() - 1 , 1);
  matrix.writeScreen();
}

void DrawBoard::drawHorizontalLines(int x, int y, int verticalDistance, int horizontalDistance, Adafruit_HT1632LEDMatrix matrix) {
  matrix.drawLine(x, y, x + verticalDistance, y, 1);
  matrix.drawLine(x, y + horizontalDistance, x + verticalDistance, y + horizontalDistance, 1);
  matrix.writeScreen();
}