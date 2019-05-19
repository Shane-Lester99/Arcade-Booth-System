#include "Arduino.h"
#include "game_logic.h"A


TicTacToe::TicTacToe() {
  randomSeed(analogRead(A3));
	// Counts number of tiles open
	posFilled = 0;
	// init to 2 so we can make player 1 go first in loop.
	playerTurn = 2;
}

void TicTacToe::resetGame() {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      gamePieces[i][j] = "";
    }
  }
  playerTurn = 2;
  posFilled = 0;
  systemGameMode = "";
  computerTurn = -1;
}

void TicTacToe::chooseGameMode(String gameMode) {
  systemGameMode = gameMode;
}
	
String TicTacToe::getGameMode() const {
  return systemGameMode;
}
	
void TicTacToe::selectItemsForSinglePlayerGameMode(int firstOrSecond) {
	if (firstOrSecond == 0) {
		computerTurn = 2;
	}
	else {
		computerTurn = 1;
	}
}

	
bool TicTacToe::isComputersTurn() const {
  if (playerTurn == computerTurn) {
    return true;
  }
  return false;
}

int TicTacToe::makeDecision() const {
  // AI implemented here. Right now it is just random
	int positionDecision = chooseRandomOpenPosition();
	return positionDecision;
}

int TicTacToe::chooseRandomOpenPosition() const {
  int openPositions[9];
  int count = 0;
	int pos = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (gamePieces[i][j] != "x" && gamePieces[i][j] != "o") {
				openPositions[count] = pos;
				count++;
			}
			pos++;
		}
	}
	// Now we will choose a random index for the vector 
	// to get our random position
	int randomIndex = random(0,8) % count;
	int randomPosition = openPositions[randomIndex];
	return randomPosition;
}

String TicTacToe::boardHasAtPosition(int pos) {
  if (pos == 0) {
		return gamePieces[0][0];
	}
	else if (pos == 1) {
		return gamePieces[0][1];
	}
	else if (pos == 2) {
		return gamePieces[0][2];
	}
	else if (pos == 3) {
		return gamePieces[1][0];
	}
	else if (pos == 4) {
		return gamePieces[1][1];
	}
	else if (pos == 5) {
		 return gamePieces[1][2];
	}
	else if (pos == 6) {
	  return gamePieces[2][0];
	}
	else if (pos == 7) {
	  return gamePieces[2][1];
	}
	else if (pos == 8) {
	  return gamePieces[2][2];	
	}
}

bool TicTacToe::takeSlot(int pos, const String& piece) {
	if (piece != "x" && piece != "o") {
		return false;
	}
	if (pos == 0) {
		if (gamePieces[0][0] == "x" || gamePieces[0][0] == "o") {
			return false;
		}
		gamePieces[0][0] = piece;
	}
	else if (pos == 1) {
		if (gamePieces[0][1] == "x" || gamePieces[0][1] == "o") {
			return false;
		}
		gamePieces[0][1] = piece;
	}
	else if (pos == 2) {
		if (gamePieces[0][2] == "x" || gamePieces[0][2] == "o") {
			return false;
		}
		gamePieces[0][2] = piece;
		
	}
	else if (pos == 3) {
		if (gamePieces[1][0] == "x" || gamePieces[1][0] == "o") {
			return false;
		}
		gamePieces[1][0] = piece;
		
	}
	else if (pos == 4) {
		if (gamePieces[1][1] == "x" || gamePieces[1][1] == "o") {
			return false;
		}
		gamePieces[1][1] = piece;
		
	}
	else if (pos == 5) {
		if (gamePieces[1][2] == "x" || gamePieces[1][2] == "o") {
			return false;
		}
		gamePieces[1][2] = piece;
	}
	else if (pos == 6) {
		if (gamePieces[2][0] == "x" || gamePieces[2][0] == "o") {
			return false;
		}
		gamePieces[2][0] = piece;
	}
	else if (pos == 7) {
		if (gamePieces[2][1] == "x" || gamePieces[2][1] == "o") {
			return false;
		}
		gamePieces[2][1] = piece;
	}
	else if (pos == 8) {
		if (gamePieces[2][2] == "x" || gamePieces[2][2] == "o") {
			return false;
		}
		gamePieces[2][2] = piece;
	}
	posFilled++;
	return true;
}

String TicTacToe::checkIfPreviousPlayerWon() {
	bool win = checkWinConditions();
	if (win) {
		return "win";
	}
	else if (posFilled == 9) {
	  return "tie";
	}
	else {
		return "nobody_won";
	}
}


bool TicTacToe::checkWinConditions() const {
	String playerToCheck = getPiece();
	for (int i = 0; i < 3; i++) {
		// Check horizontal columns
		if (gamePieces[i][0] == playerToCheck && gamePieces[i][1] == playerToCheck && gamePieces[i][2] == playerToCheck) {
			return true;
		}
		// Check vertical columns
		if (gamePieces[0][i] == playerToCheck && gamePieces[1][i] == playerToCheck && gamePieces[2][i] == playerToCheck) {
			return true;
		}
	}
	// Diagonal
	if (gamePieces[0][0] == playerToCheck && gamePieces[1][1] == playerToCheck && gamePieces[2][2] == playerToCheck) {
			return true;
	}
	// Reverse Diagonal
	if (gamePieces[0][2] == playerToCheck && gamePieces[1][1] == playerToCheck && gamePieces[2][0] == playerToCheck) {
			return true;
	}
	return false;

}
	
String TicTacToe::getPiece() const {
  String piece;
	if (playerTurn == 1) {
		piece = "x";
	} else {
		piece = "o";
	}
	return piece;
}

void TicTacToe::switchPlayer() {
	if (playerTurn == 1) {
		playerTurn = 2;
	} else {
		playerTurn = 1;
	}
	return;
}