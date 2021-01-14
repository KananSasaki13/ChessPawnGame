#include <iostream>
#include <string>

using namespace std;

class Piece{

public:
    //Typedefs
    typedef pair<int, int> Position;

    //Queries
    virtual bool isAttack(char color, Position currentPos, Position newPos);
    virtual bool validateMove(char color, Position currentPos, Position newPos);
    char getColor();
    char getName();
    bool getIsEmpty();
    bool getIsFirstMove();
    Position getPosition();

    //Commands
    void makeMove(Position newPos);
    void setColor(char c);
    void setPiece(Position p);
    void setName(char c);
    void setIsEmpty();
    void setIsFirstMove();

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
    cout << "in piece attack" << endl;
    return false;
}

bool Piece::validateMove(char color, Position currentPos, Position newPos)
{
    cout << "in piece validate move" << endl;
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
    cout << "SettingIsFirstMove to false" << endl;
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
