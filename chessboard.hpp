#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "pawn.hpp"
#include <typeinfo>

using namespace std;

const int rows = 8;
const int cols = 8;

class ChessBoard {

public:
    //Destructor/Constructor
    ~ChessBoard();
    ChessBoard();

    //Typedefs
    typedef pair<int, int> Position;

    //Commands
    friend ostream& operator<<(ostream& os, const ChessBoard& board);
//    void setNewBoard();
    void makeMove(char color, Position selectedPiece, Position selectedPosition);

    //Queries
//    unique_ptr<Piece> getPieceAtPosition(Position p);
    bool spaceHasPiece(Position p);
    bool oppHasNoPawns(char color);
    bool hasPawnOnLastRank(char color);
    bool oppHasNoAvailableMove(char color);
    bool isValidMove(char color, Position piece, Position pos);
    vector< vector< unique_ptr<Piece> > > boardState;

private:


};

//Destructor
ChessBoard::~ChessBoard()
{
    cout << "Deconstructing the board" << endl;
}

//Constructor
ChessBoard::ChessBoard ()
{
    cout << "Constructing the board" << endl;
    for(int row = 0; row < 8; row++)
    {
        vector<unique_ptr<Piece>> temp;
        for(int col = 0; col < 8; col++)
        {
            if(row == 1)
                temp.emplace_back(new Pawn('B', make_pair(row, col)));
            else if(row == 6)
                temp.emplace_back(new Pawn('W', make_pair(row, col)));
            else
                temp.emplace_back(new Piece());
        }
        boardState.emplace_back(move(temp));
    }
}

//Commands
ostream& operator<<(ostream& os, ChessBoard& board)
{
    cout << endl;
    int i=1, j;

    //Print Rows
    for(i = 0; i <=  2*rows; i++){
        //Print Rank Headers (1-8)
        if(i % 2 != 0)
          cout << rows - i/2;
        for(j = 0; j <= 2*cols; j++){
          if(i % 2 == 0) {
            if(j == 0)
                cout << " ";
            if(j % 2 == 0)
                cout << " ";
            else cout << "----";
          }
          else{
            if(j % 2 == 0)
                cout << "|";
            else {
                if(board.spaceHasPiece(make_pair(i/2,j/2))){
                    printf(" %c%c ", board.boardState[i/2][j/2]->getColor(), board.boardState[i/2][j/2]->getName());
//                    printf(" %d%d ", i/2,j/2);
                }
                else
                    cout << "    ";
            }
          }
        }
        cout << endl;
    }

    //Print File Headers (a-h)
    cout << " ";
    for(j = 0; j <= 4*cols; j++){
        if(j % 4 == 2)
            cout << (char)(j/4 +'a') << '.';
        else cout << " ";
    }
    cout << endl;

    return os;
}

//Sets up a new board. Currently will set the second and seventh ranks with pawns. Can be modified later to setup other pieces.
//void ChessBoard::setNewBoard()
//{
//    cout << "setNewBoard" << endl;
//    for(int row = 0; row < 8; row++)
//    {
//        for(int col = 0; col < 8; col++)
//        {
//            boardState[col].emplace_back(new Pawn('B', make_pair(col, 1)));
//        }
////        boardState[1][col] = Pawn('B', make_pair(col, 1));
////        boardState[6][col] = Pawn('W', make_pair(col, 6));
//    }
//}

void ChessBoard::makeMove(char color, Position selectedPiece, Position selectedPosition)
{
    if(boardState[selectedPosition.first][selectedPosition.second]->isAttack(color, selectedPiece, selectedPosition))
    {
        boardState[selectedPosition.first][selectedPosition.second]->setIsEmpty();
        swap(boardState[selectedPosition.first][selectedPosition.second], boardState[selectedPiece.first][selectedPiece.second]);
    }
    else
        swap(boardState[selectedPosition.first][selectedPosition.second], boardState[selectedPiece.first][selectedPiece.second]);
    boardState[selectedPosition.first][selectedPosition.second]->setIsFirstMove();
}

bool ChessBoard::spaceHasPiece(Position p)
{
    return !boardState[p.first][p.second]->getIsEmpty();
}

bool ChessBoard::oppHasNoPawns(char color)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if(!(boardState[i][j]->getColor() == 'N' || boardState[i][j]->getColor() == color))
                return false;
        }
    }
    return true;
}

bool ChessBoard::hasPawnOnLastRank(char color)
{
    if(color == 'W')
    {
        for(int i = 0; i < cols; i++)
        {
            if(boardState[0][i]->getColor() == 'W')
                return true;
        }
    }
    return false;
}

bool ChessBoard::oppHasNoAvailableMove(char color)
{
    return false;
}

bool ChessBoard::isValidMove(char color, Position piece, Position pos)
{
    if(boardState[piece.first][piece.second]->validateMove(color, piece, pos))
    {
        if(boardState[piece.first][piece.second]->getName() == 'P')
            if(spaceHasPiece(pos) && !boardState[piece.first][piece.second]->isAttack(color, piece, pos))
                return false;
        return true;
    }
    else {
        return false;
    }
}
