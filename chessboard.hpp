#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "pawn.hpp"
#include <typeinfo>

/*
    This class maintains the information of the chessboard.
    Includes positions of pieces and the logic for verifying moves and checking for victory/draw conditions.
*/

using namespace std;

//Global variables for the number of rows and columns. Typically for a normal chessboard it is an 8x8 board.
const int rows = 8;
const int cols = 8;

class ChessBoard {

public:
    //Constructor
    ChessBoard();

    //Typedefs
    typedef pair<int, int> Position;

    //Commands
    friend ostream& operator<<(ostream& os, const ChessBoard& board);
    void makeMove(char color, Position selectedPiece, Position selectedPosition);

    //Queries
    bool spaceHasPiece(Position p);
    bool pieceIsColor(Position p, char color);
    bool oppHasNoPawns(char color);
    bool hasPawnOnLastRank(char color);
    bool oppHasNoAvailableMove(char color);
    bool isValidPosition(Position p);
    bool isValidMove(char color, Position piece, Position pos);
    vector< vector< unique_ptr<Piece> > > boardState;

};

//Constructor
ChessBoard::ChessBoard ()
{
    for(int row = 0; row < 8; row++)
    {
        vector<unique_ptr<Piece>> temp;
        for(int col = 0; col < 8; col++)
        {
            //Comment these lines out and remove the comments below to test draw/win scenario.
            if(row == 1)
                temp.emplace_back(new Pawn('B', make_pair(row, col)));
            else if(row == 6)
                temp.emplace_back(new Pawn('W', make_pair(row, col)));
            else
                temp.emplace_back(new Piece());

            //This can be used to easily test a draw or win scenario.
//            if(row == 3 && col % 2 == 0)
//                temp.emplace_back(new Pawn('B', make_pair(row, col)));
//            else if(row == 4 && col % 2 == 0)
//                temp.emplace_back(new Pawn('W', make_pair(row, col)));
//            else if(row == 4 && col % 2 == 1 && col != 7)
//                temp.emplace_back(new Pawn('B', make_pair(row, col)));
//            else if(row == 5 && col % 2 == 1)
//                temp.emplace_back(new Pawn('W', make_pair(row, col)));
//            else
//                temp.emplace_back(new Piece());
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

void ChessBoard::makeMove(char color, Position selectedPiece, Position selectedPosition)
{
    //If the move is an attack, need to swap the position with an empty Piece
    if(boardState[selectedPosition.first][selectedPosition.second]->isAttack(color, selectedPiece, selectedPosition))
    {
        boardState[selectedPosition.first][selectedPosition.second]->setIsEmpty();
        swap(boardState[selectedPosition.first][selectedPosition.second], boardState[selectedPiece.first][selectedPiece.second]);
    }
    //If the move is a regular move, simply swap the existing empty Piece with the used piece
    else
        swap(boardState[selectedPosition.first][selectedPosition.second], boardState[selectedPiece.first][selectedPiece.second]);
    boardState[selectedPosition.first][selectedPosition.second]->setIsFirstMove();
}

bool ChessBoard::spaceHasPiece(Position p)
{
    return !boardState[p.first][p.second]->getIsEmpty();
}

bool ChessBoard::pieceIsColor(Position p, char color)
{
    return boardState[p.first][p.second]->getColor() == color;
}

bool ChessBoard::oppHasNoPawns(char color)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            //Check if a space contains a piece of the opposing color
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
    else
    {
        for(int i = 0; i < cols; i++)
        {
            if(boardState[7][i]->getColor() == 'B')
                return true;
        }
    }
    return false;
}

//Check if the opponent has an available move. This is necessary to determine both the victory condition and the draw condition.
bool ChessBoard::oppHasNoAvailableMove(char color)
{
    if(color == 'W')
    {
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                if(boardState[i][j]->getColor() == 'B')
                {
                    if(isValidMove('B', make_pair(i,j), make_pair(i+1, j)) || isValidMove('B', make_pair(i,j), make_pair(i+1, j+1)) || isValidMove('B', make_pair(i,j), make_pair(i+1, j-1)))
                        return false;
                }
            }
        }
    }
    else
    {
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                if(boardState[i][j]->getColor() == 'W')
                {
                    if(isValidMove('W', make_pair(i,j), make_pair(i-1, j)) || isValidMove('W', make_pair(i,j), make_pair(i-1, j+1)) || isValidMove('W', make_pair(i,j), make_pair(i-1, j-1)))
                        return false;
                }
            }
        }
    }

    return true;
}

//Checks to make sure that the provided coordinates fit within the grid.
bool ChessBoard::isValidPosition(Position p)
{
    if(p.first < rows && p.first >= 0 && p.second < cols && p.second >= 0)
        return true;
    return false;
}

bool ChessBoard::isValidMove(char color, Position piece, Position pos)
{
    //If the current piece position and the desired move position are within the grid parameters
    if(isValidPosition(piece) && isValidPosition(pos))
    {
        //If the piece that was selected is capable of moving to the desired position
        if(boardState[piece.first][piece.second]->validateMove(color, piece, pos))
        {
            //If the space has a piece
            if(spaceHasPiece(pos))
            {
                //If the desired move position's piece's color does not match the selected piece
                if(boardState[piece.first][piece.second]->getColor() != boardState[pos.first][pos.second]->getColor())
                {
                    //Check for pawns
                    if(boardState[piece.first][piece.second]->getName() == 'P')
                        //If it is a pawn, check to see if the move is a valid attack
                        if(!boardState[piece.first][piece.second]->isAttack(color, piece, pos))
                            return false;
                    return true;
                }
            }
            else //If the space does not have a piece
            {
                //Check for pawns
                if(boardState[piece.first][piece.second]->getName() == 'P')
                    //Check if the move is a pawn attack
                    if(boardState[piece.first][piece.second]->isAttack(color, piece, pos))
                        return false;
                return true;
            }
        }
    }
    return false;
}
