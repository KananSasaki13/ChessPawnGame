#include <iostream>
#include <string>
#include "piece.hpp"
#include <cmath>
#include <iostream>

using namespace std;

class Pawn: public Piece {

private:
    //Variables


public:
    //Destructor/Constructor
    ~Pawn();
    Pawn(char myColor, Position p);

    //Queries
    bool isAttack(char color, Position currentPos, Position newPos);
    bool validateMove(char color, Position currentPos, Position newPos);

};

Pawn::~Pawn()
{
    cout << "Deconstructing a pawn" << endl;
}

Pawn::Pawn (char myColor, Position p)
{
    cout << "Constructing a pawn" << endl;
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

    cout << "IsFirstMove = " << getIsFirstMove() << endl;
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

