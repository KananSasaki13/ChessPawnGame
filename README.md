# ChessPawnGame
C++ project to play chess pawn game.

This project is meant to simulate a chess pawn game (see details at this link: http://www.chesscorner.com/tutorial/basic/pawngame/pawngame.htm).
I decided that this project would be a good one because it demonstrates my ability to both build a simple completed project while also showing that I am capable of coding/planning
for a larger scale project.

The classes provided are:
1. main.cpp -> constructs and runs the game

2. piece.hpp -> this is my base class for all spaces/pieces on the board and is inherited by the pawn.hpp class. I have constructed this class to take generic information for a
given piece on the board, with virtual functions on moving and attacking. This is the class that will be used to construct our 2d vector board of pointers towards the pieces.
The reason why we must use a 2d vector of pointer pieces rather than a 2d vector of pieces is that we need to avoid object splicing when 
attempting to set a space to a derived object (such as a pawn).

3. pawn.hpp -> this is the only piece that is used in the pawn game, but would serve as a template on how to construct the other pieces for a complete chess game. It inherits
the piece.hpp class and contains a pawn's logic. 

4. chessboard.hpp -> maintains the information of the chessboard. Includes positions of pieces and the logic for verifying moves and checking for victory/draw conditions.

5. gamestate.hpp -> this class contains the logic for actually running the game through the console. It has methods for prompting for pieces, running the game and displaying the ui.

//Description
Welcome to the Chess Pawn Game!

Remember pawns move one square forward (never backward) except on their first move when they have a choice of moving either one or two squares. 
They capture by moving one square forward diagonally.

You win the game:
a) if you are the first to capture all your opponent's pawns; or
b) if you are the first to reach the last rank (i.e. your opponent's first rank) with one of your pawns; or
c) if it is your opponent's turn to move but all her pawns are blocked and do not have any moves, while you yourself can make at least one move.

To make a move:
Select a space on the board containing one of your pieces by using a character-integer combination (ie. f3 or h1). Then select a space on the board you would like to move to.
