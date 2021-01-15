#include "chessboard.hpp"

using namespace std;

class GameState {

public:
    //Typedefs
    typedef pair<int, int> Position;

    //Queries
    char getTurn();
    bool checkForVictory();
    bool checkForDraw();

    //Commands
    void switchTurn();
    void takeTurn();
    void runGame();

private:
    ChessBoard board;
    char currentPlayer = 'W';

    //Queries
    bool validateResponse(string response);
    Position promptForPiece();
    Position promptForMove();
    int getRankFromLetter(char c);
};

//Queries
int GameState::getRankFromLetter(char c)
{
    switch(c)
    {
    case 'a':
        return 0;
    case 'b':
        return 1;
    case 'c':
        return 2;
    case 'd':
        return 3;
    case 'e':
        return 4;
    case 'f':
        return 5;
    case 'g':
        return 6;
    case 'h':
        return 7;
    default:
        return -1;
    }
}

char GameState::getTurn()
{
    return currentPlayer;
}

bool GameState::checkForVictory()
{
    //Victory Conditions for Pawn game
    //a) if you are the first to capture all your opponent's pawns; or
    //b) if you are the first to reach the last rank (i.e. your opponent's first rank) with one of your pawns; or
    //c) if it is your opponent's turn to move but all her pawns are blocked and do not have any moves, while you yourself can make at least one move.

    if(board.oppHasNoPawns(currentPlayer))
        return true;
    else if(board.hasPawnOnLastRank(currentPlayer))
        return true;
    else if(board.oppHasNoAvailableMove(currentPlayer))
        return true;
    return false;
}

bool GameState::checkForDraw()
{
    //Draw Condition for Pawn game
    //If both sides' pawns are blocked so that neither side can make a move

    if(board.oppHasNoAvailableMove('W') && board.oppHasNoAvailableMove('B'))
        return true;
    return false;
}

bool GameState::validateResponse(string response)
{
    if(response.length() != 2)
        throw "Please provide correct number of characters";
    else
    {
        if(!isalpha(response[0]) || !isdigit(response[1]))
            throw "Please provide correct col-rank pair format (ie. f3 or h1)!";
        else
        {
            if(getRankFromLetter(response[0]) < 0 || rows - (response[1] - '0') < 0 || rows - (response[1] - '0') > 7)
                throw "Please provide correct col-rank pair within the bounds of the board!";
        }
    }
    return true;
}

pair<int, int> GameState::promptForPiece()
{
    string square;
    cout << "Select a piece on the board by typing in the square it is in (ie. f3 or h1)" << endl;
    cin >> square;

    int row, file;
    char col;
    try
    {
        if(validateResponse(square))
        {
            col = square[0];
            row = rows - (square[1] - '0');
            file = getRankFromLetter(col);
        }
    }
    catch (const char* msg)
    {
        cout << msg << endl;
        return promptForPiece();
    }

    if(board.spaceHasPiece(make_pair(row, file)))
    {
        return make_pair(row, file);
    }

    cout << "That square is empty. Please try again." << endl;
    return promptForPiece();
}

pair<int, int> GameState::promptForMove()
{
    string square;
    cout << "Select a space to move your piece on the board by typing in the square it is in (ie. f3 or h1)" << endl;
    cin >> square;

    int row, file;
    char col;

    try
    {
        if(validateResponse(square))
        {
            col = square[0];
            row = rows - (square[1] - '0');
            file = getRankFromLetter(col);
        }
    }
    catch (const char* msg)
    {
        cout << msg << endl;
        return promptForMove();
    }

    return make_pair(row, file);
}

//Commands
void GameState::switchTurn()
{
    if(currentPlayer == 'W')
    {
        currentPlayer = 'B';
    }
    else
    {
        currentPlayer = 'W';
    }
}

void GameState::takeTurn()
{
    Position selectedPiece = promptForPiece();
    cout << endl;
    Position selectedPosition = promptForMove();
    while(!board.isValidMove(currentPlayer, selectedPiece, selectedPosition))
    {
        cout << "This is not a valid move. Please select again." << endl;
        selectedPiece = promptForPiece();
        selectedPosition = promptForMove();
    }
    board.makeMove(currentPlayer, selectedPiece, selectedPosition);
}

void GameState::runGame()
{
    cout << "Welcome to chess pawn game! Be the first to reach the last rank or capture all of your opponent's pawns." << endl;

    while(true)
    {
        cout << board << endl;
        printf("It's %c's turn.\n", currentPlayer);
        cout << endl;

        if(checkForDraw())
        {
            cout << "The game is a draw!" << endl;
            break;
        }
        if(checkForVictory())
        {
            if(currentPlayer == 'W')
            {
                cout << "White is the winner!" << endl;
            } else {
                cout << "Black is the winner!" << endl;
            }
            break;
        }

        takeTurn();
        switchTurn();
    }
}
