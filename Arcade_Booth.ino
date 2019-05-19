/*
'Main function' of the program.

Contains all the modules and the gameplay loop. Interfaces between the rest
of the modules in the program.
*/


// Downloaded Here" https://github.com/adafruit/Adafruit-GFX-Library
#include "Adafruit_GFX.h"

// Downloaded Here: https://github.com/adafruit/HT1632
#include "Adafruit_HT1632.h"

// Modules used in program **********

// Displays menus and output messages
#include "menu.h"
// Draws to the board
#include "draw_board.h"
// Driver for the joystick analog input
#include "joystick.h"
// All the game data and control
#include "game_logic.h"

// Constant pins for the LED Matrix
#define HT_DATA 2
#define HT_WR   3
#define HT_CS   4
#define HT_CS2  5

// Constant pin to read the button
#define READ_BUTTON 12


// LED MATRIX **************************
Adafruit_HT1632LEDMatrix matrix = Adafruit_HT1632LEDMatrix(HT_DATA, HT_WR, HT_CS, HT_CS2);


// Objects from each module ************

// Draws all objects on the board
DrawBoard gameBoard;

// Contains all the menus on the screen and popup messages
Menu menu;

// Contains the input joystick. Handles the analog input to provide a
// easy to use interface
Joystick joystick;

// The game logic behind tic tac toe. All the data and functions to play the
// game are held here.
TicTacToe gameLogic;

// This will choose the position during the game. It communicates with the 
// gameLogic object, the Joystick object, the button, and the gameBoard to
// read in input, draw the correct object, and save the data to the gameLogic
// object
void choosePosition(char turn) {
  // This will run until the player has taken a position
  // inits at middle square
  int gamePos = 4;
  while (true) {
    delay(100);
    String dir = joystick.isDirection();
    if (dir ==  "A: Nuetral, B: Down") {
      if (gamePos + 3 < 9) {
          gamePos += 3;
      }
      Serial.print("down\n");
    }
    else if (dir ==  "A: Nuetral, B: Up") {
      if (gamePos - 3 >= 0) {
        gamePos -= 3;
      }
      Serial.print("up\n");
    }
    else if (dir ==  "A: Left, B: Nuetral") {
      if (gamePos - 1 >= 0) {
        gamePos -= 1;
      }
       Serial.print("left\n");
    }
    else if (dir == "A: Right, B: Nuetral") {
      if (gamePos + 1 < 9) {
        gamePos += 1;
      }
      Serial.print("right\n");
    }
    Serial.print("Game Pos");
    Serial.print(gamePos);
    Serial.print("\n");
    // This will blink the correct piece as it is being selected.
    gameBoard.blinkBeforeSelection(turn, gamePos, matrix);
    // This will rewrite the object so that it doesnt dissapear
    // from board after blinking
    String overwrite = gameLogic.boardHasAtPosition(gamePos);
    if (overwrite == "o") {
      gameBoard.writePosition('o', gamePos, true, matrix);
    }
    else if (overwrite == "x") {
      gameBoard.writePosition('x', gamePos, true, matrix);
    }
    // This will read if the button is pushed, if so it will
    // try to take the slot and write to it (but only if its free)
    if ( digitalRead(READ_BUTTON) == LOW ) {
      // If we have found a slot, then we win
      if (gameLogic.takeSlot(gamePos, String(turn))) {
        gameBoard.writePosition(turn, gamePos, true, matrix);
        break;
      }
    }
  }
}

//  This will choose if it is multiplayer or single player.
void howManyPlayers() {
  String ans = menu.chooseMode(joystick, matrix);
  gameLogic.chooseGameMode(ans);
}

void setup() {
  
  Serial.begin(9600);
  matrix.begin(ADA_HT1632_COMMON_16NMOS);
 
  // Print Welcome to tic tac toe on entrance 
  menu.printIntroScreen(matrix);
  
  // This will init the pins A0, A1 to read from joystick
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  // This will init the pin 12 to be input via button
  pinMode(READ_BUTTON, INPUT_PULLUP);
}

void loop() {
  // Chooses single or multiplayer
  howManyPlayers();
  // Draws game board
  gameBoard.initGameBoard(matrix);
  // Multiplayer mode
  if (gameLogic.getGameMode() == "multi") {
    // Init winstring to "nobody_won"
    String winstring = gameLogic.checkIfPreviousPlayerWon();
    // We need to check every loop if the player won.
	  while (winstring == "nobody_won") {
	    // Switch the player every turn.
		  gameLogic.switchPlayer();
		  // Choose the position function will will
		  // handle communication between all modules.
		  choosePosition(gameLogic.getPiece()[0]);
		  // Now the user has chosen a position. So check if they won.
		  winstring = gameLogic.checkIfPreviousPlayerWon();
	  }
	  // Display win message.
	  if (winstring == "win") {
	    if (gameLogic.getPiece() == "x") {
	      winstring = "Player 1 wins!";
	    } else {
	      winstring = "Player 2 wins!";
	    }
	  	menu.displayEndMessage(winstring, matrix);
	  } else {
		  menu.displayEndMessage("Tie!", matrix);
	  }
	  // Reset the game.
	  gameLogic.resetGame();
	  
  } else {
    // Init winstring to "nobody_won"
    String winstring = gameLogic.checkIfPreviousPlayerWon();
    // This will choose who goes first (Currently disabled functionality to
    // allow computer to be x.)
    gameLogic.selectItemsForSinglePlayerGameMode(0);
    // Enter loop until someone wins
    while (winstring == "nobody_won") {
      gameLogic.switchPlayer();
    // We need to check if its the CPU or the user
    if (gameLogic.isComputersTurn()) {
      // AI will choose position here. Note that this is where AI
      // algorithm MiniMax would be iterated on.
      int aiChoosePosition = gameLogic.makeDecision();
      // Delay turn so it seems like AI is 'thinking'
      delay(2000);
      // Allow the AI to take the space and write to it.
      gameLogic.takeSlot(aiChoosePosition, gameLogic.getPiece());
      gameBoard.writePosition(gameLogic.getPiece()[0], aiChoosePosition, true, matrix);
      delay(2000);
    } else {
        // This will run until the player has taken a position
		    choosePosition(gameLogic.getPiece()[0]);
		    // Now the user has chosen a position. Check if they won.
		    winstring = gameLogic.checkIfPreviousPlayerWon();
      }
      winstring = gameLogic.checkIfPreviousPlayerWon();
    }
    // Win message  
    if (winstring == "win") {
	  	 if (gameLogic.getPiece() == "x") {
	      winstring = "Human wins!";
	    } else {
	      winstring = "AI wins!";
	    }
	    menu.displayEndMessage(winstring, matrix);
	  } else {
		  menu.displayEndMessage("Tie!", matrix);
	  }
	  // Game is reset
	   gameLogic.resetGame();
  }
}
   