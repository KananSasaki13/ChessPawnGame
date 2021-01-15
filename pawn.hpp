#include "piece.hpp"
#include <cmath>
#include <iostream>

/*
    This is the only piece that is used in the pawn game.
    This class should be used as a template on how to construct the other pieces for a complete chess game (ie. king, knight, rook, etc.).
    It inherits the piece.hpp class and contains a pawn's logic.
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
            return true;
        else
            return false;
    } else { //Black Pawn
        //Attack
        if(newPos.first - currentPos.first == 1 && abs(newPos.second - currentPos.second) == 1)
            return true;
        else
            return false;
    }
}

bool Pawn::validateMove(char color, Position currentPos, Position newPos) {
    //White Pawn
    if(color == 'W')
    {
        //Check Attack and Move
        if((currentPos.first - newPos.first == 1 || (getIsFirstMove() && currentPos.first - newPos.first == 2)) && abs(newPos.second - currentPos.second) <= 1)
            return true;
        else
            return false;
    } else { //Black Pawn
        //Check Attack and Move
        if((newPos.first - currentPos.first == 1 || (getIsFirstMove() && newPos.first - currentPos.first == 2)) && abs(newPos.second - currentPos.second) <= 1)
            return true;
        else
            return false;
    }
}

