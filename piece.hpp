#include <iostream>
#include <string>

/*
    This class is the base class for all derived pieces and pointers to these objects will represent
    empty spaces on the board. It carries several of the core variables for chess pieces
    (color, name of the piece, etc.).

    This is the class that will be used to construct our 2d vector board of pointers towards the pieces.
    The reason why we must use a 2d vector of pointer pieces rather than a 2d vector of pieces is that
    we need to avoid object splicing when attempting to set a space to a derived object (such as a pawn).
*/

using namespace std;

class Piece{

public:
    //Typedefs
    typedef pair<int, int> Position;

    //Queries
    char getColor();
    char getName();
    bool getIsEmpty();
    bool getIsFirstMove();
    Position getPosition();
    virtual bool isAttack(char color, Position currentPos, Position newPos);
    virtual bool validateMove(char color, Position currentPos, Position newPos);

    //Commands
    void setColor(char c);
    void setName(char c);
    void setIsEmpty();
    void setIsFirstMove();
    void makeMove(Position newPos);
    void setPiece(Position p);

private:
    //Variables
    char color = 'N';
    char name = 'X';
    bool isEmpty = true;
    bool isFirstMove = true;
    Position currentPosition;

};

bool Piece::isAttack(char color, Position currentPos, Position newPos)
{
    return false;
}

bool Piece::validateMove(char color, Position currentPos, Position newPos)
{
    return false;
}

void Piece::setColor(char c)
{
    color = c;
}

void Piece::setName(char c)
{
    name = c;
}

void Piece::setPiece(Position p)
{
    currentPosition = p;
    isEmpty = false;
}

void Piece::setIsEmpty()
{
    isEmpty = true;
}

void Piece::setIsFirstMove()
{
    isFirstMove = false;
}

char Piece::getColor()
{
    return color;
}

char Piece::getName()
{
    return name;
}

bool Piece::getIsEmpty()
{
    return isEmpty;
}

bool Piece::getIsFirstMove()
{
    return isFirstMove;
}

pair<int, int> Piece::getPosition()
{
    return currentPosition;
}
