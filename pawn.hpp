#include "piece.hpp"
#include <cmath>
#include <iostream>

/*
    This class is the base class for all derived pieces and pointers to these objects will represent
    empty spaces on the board. It carries several of the core variables for chess pieces
    (color, name of the piece, etc.).

    This is the class that will be used to construct our 2d vector board of pointers towards the pieces.
    The reason why we must use a 2d vector of pointer pieces rather than a 2d vector of pieces is that
    we need to avoid object splicing when attempting to set a space to a derived object (such as a pawn).
*/

using namespace std;

class Pawn: public Piece {

public:
    //Constructor
    Pawn(char myColor, Position p);

    //Queries
    bool isAttack(char color, Position currentPos, Position newPos);
    bool validateMove(char color, Position currentPos, Position newPos);

};

Pawn::Pawn (char myColor, Position p)
{
    setColor(myColor);
    setName('P');
    setPiece(p);
}

bool Pawn::isAttack(char color, Position currentPos, Position newPos)
{
    if(color == 'W')
    {
        //Attack
        if(currentPos.first - newPos.first == 1 && abs(newPos.second - currentPos.second) == 1)
        {
            return true;
        } else {
            return false;
        }
    } else { //Black Pawn
        //Attack
        if(newPos.first - currentPos.first == 1 && abs(newPos.second - currentPos.second) == 1)
        {
            return true;
        } else {
            return false;
        }
    }
}

bool Pawn::validateMove(char color, Position currentPos, Position newPos) {
    //White Pawn
    if(color == 'W')
    {
        //Attack and Move
        if((currentPos.first - newPos.first == 1 || getIsFirstMove() && currentPos.first - newPos.first == 2) && abs(newPos.second - currentPos.second) <= 1)
        {
            return true;
        } else {
            return false;
        }
    } else { //Black Pawn
        //Attack and Move
        if((newPos.first - currentPos.first == 1 || getIsFirstMove() && newPos.first - currentPos.first == 2) && abs(newPos.second - currentPos.second) <= 1)
        {
            return true;
        } else {
            return false;
        }
    }
}

