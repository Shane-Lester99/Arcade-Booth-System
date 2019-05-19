/*
Game Logic module

Contains all the data and functionality of game. The game is run through this module.
In fact, this module can be augmented to run on different interfaces. Here it is 
made to run on the arduino uno.
*/

#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "Arduino.h"

class TicTacToe {
	public:
	TicTacToe();
	
	// Will set game between single and multiplier given string indicating which.
	void chooseGameMode(String gameMode);
	
	// Will return which game mode it is (single or multiplier)
	String getGameMode() const;
	
	// This will decide if the player (vs computer) is first or second.
	// Note: This is runnable in system but omitted from embedded systen.
	void selectItemsForSinglePlayerGameMode(int firstOrSecond);

  // Chooses the move for the computer. TODO: Implement AI algorithm here. Currently random position.
  // The AI is currently very very dumb.
	int makeDecision() const;

  // Chooses a random open position.
	int chooseRandomOpenPosition() const;

  // Takes a slot at pos, with a game piece piece, if the slot isnt taken.
	bool takeSlot(int pos, const String& piece);
	
	// Checks if theres a win or a tie. A tie is every slot is taken and no one won.
	String checkIfPreviousPlayerWon();
	
	// Check if their is a game win.
	bool checkWinConditions() const;
  
  // Checks what piece is at a particular position.	
	String boardHasAtPosition(int pos);

  // Get the piece for the current turn.	
	String getPiece() const;

  // Swithecs the player. So if it is player 1, this function will switch to player 2. Vice versa.
	void switchPlayer();
	
	// Resets all the game data to play another game.
	void resetGame();
	
	// Checks if it is the computers turn.
	bool isComputersTurn() const;

	private:
	// where 'x' and 'o' are stored
	String gamePieces[3][3];
	// can either be 1 or 2
	int playerTurn;
	// Counts how many pieces are on the board to keep track of ties
	int posFilled;

  // Stores if its single or multi mode
  String systemGameMode;

	//Only applicable for single player mode
	int computerTurn;
};

#endif