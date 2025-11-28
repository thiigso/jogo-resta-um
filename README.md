# Objective

The objective of this code is to create a Peg Solitaire game (known in Portuguese as Resta Um), in which the user can use the arrow keys on the keyboard to move around the board, select a piece, and make a move. The game works the same way as a traditional Peg Solitaire game.


# Rules and Instructions

The 7x7 board is initialized in a cross shape, meaning the four corner positions are inaccessible.
All accessible positions on the board start with pieces (value = 1), except for the center position, which is empty (value = 0).

You can “capture” pieces by jumping one piece over another. This move can only be horizontal or vertical, and it can only occur if the piece to be captured is exactly one position away from the selected piece.

The main objective of the game is to have only one piece remaining.
If that happens, the game ends and you win.
If there are no more possible moves and more than one piece remains, the game ends and you lose.


# Functions

Matrix Initialization:
To prepare the game with predefined situations, you can use the following initialization steps:

Steps:
* Uncomment one of the predefined matrices between lines 309 and 313.
* Comment out the matrix initialization at line 306.
* Comment out the InitializeGame function at line 324.

## Functions in the Code

* CustomAbs: Returns the absolute value.
* InitializeGame: Initializes a traditional board.
* VerifyEndGame: Checks if the game has ended.
* PrintGame: Prints the board.
* CheckMove: Checks if a move is valid.
* SelectPiece: Moves and selects pieces.
