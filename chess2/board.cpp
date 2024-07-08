#include "board.h"
#include "termfuncs.h"
#include "setBoard.h"
#include <fstream>
#include <vector>

//theme = {"\033[1;30m", "\033[0m", "\033[1;100m", "\033[47m"}

void board::play(string theme[], string opponent, string gameMode, bool Dev, 
                int botColor){ 
    setUpGame(theme, gameMode, Dev, botColor);
    gameLoop(opponent, theme, gameMode);
    reviewGame(theme);
    resetGame();
}

//Sets multiple variables for game
void board::setUpGame(string theme[], string gameMode, bool Dev, int botColor){
    if(Dev){
        comments = false;
    }
    //Get initial position
    if(gameMode == "Custom Position"){
        //Delete default board and reset with custom
        startBoard.retBoard(gameBoard);
        setBoard::cleanBoard(gameBoard);
        startBoard = setBoard::customBoard(gameBoard, theme);
    }
    
    startBoard.retBoard(gameBoard);
    key = startBoard.retHalfFen();
    hashMoves[key] = true;
    boards.push_back(startBoard);

    //Variables for setting up position
    moves = startBoard.retMove50();
    allMoves = startBoard.retMoveNum();
    pessSquare = startBoard.retPessant();
    turn = startBoard.retTurn();
    castle = startBoard.retCastle();

    //If playing bot, determine who's move it is
    if(botColor){
        playBot = true;
        if(botColor == 1){
            compTurn = false;
        } else if (botColor == 2){
            compTurn = true;
        } else {
            if(rand() % 2){
                compTurn = true;
            }
        }
    }
    screen_clear();
    turn = true;
    printState(theMove, theme, gameMode);
}

//Main Game Loop
void board::gameLoop(string opponent, string theme[], string gameMode){
    (void) opponent;
    while (getline(cin, theMove)){
        screen_clear();
        if (theMove == "Quit"){
            break;
        } else if (theMove == "Resign"){
            if (turn){
                cout << "Game Over White Resigned\n\n";
            } else {
                cout << "Game Over Black Resigned\n\n";
            }
            setBoard::printBoard(gameBoard, theme, "Classic", true);
            endGame(theme);
            theMove = "Quit";
            break;
        }
        checkPiece move(gameBoard, pessSquare);
        if (move.legal(theMove, turn, castle, compTurn)){
            pieceName = gameBoard[7 - (theMove[1] - 49)][theMove[0] - 65]->name;
            move.makeMove(theMove, gameBoard, castle, comments, theme, gameMode);
            gameBoard[7 - (theMove[1] - 49)][theMove[0] - 65]->makeSpace();
            turn = !turn;
            string moveName = setBoard::pieceName(pieceName) + " from ";
            moveName += theMove.substr(0,2) + " to " + theMove.substr(3,2);
            checkPiece checkWin(gameBoard, "");
            allMoves++;
            fen currFen(gameBoard, turn, moves, allMoves, pessSquare, castle);
            key = currFen.retHalfFen();
            boards.push_back(currFen);
            if (gameOver(checkWin, theme)){
                break;
            }
            printState(moveName, theme, gameMode);
        } else {
            printState("Error - " + move.retError(), theme, gameMode);
        }
    }
}

//Prints full board with message
void board::printState(string prev, string theme[], string gameMode){
    cout << "Type \"Quit\" to quit, or \"Resign\" to resign\n\nPrevious Move: " << prev << endl << endl;
    setBoard::printBoard(gameBoard, theme, gameMode, false);
    if (comments){
        if(turn){
            cout << "\nWhite to move\n";
        } else {
            cout << "\nBlack to move\n";
        }
        cout << "Enter move (from, to): ";
    }
} 

//Checks all forms of game over
bool board::gameOver(checkPiece checkWin, string theme[]){
    if (!checkWin.canMove(turn)){
        if(checkWin.canCheck(turn)){
            gameMessage = "Game over -- Checkmate\n";
            if (turn){
                gameMessage += "Black wins!\n\n";
            } else {
                gameMessage += "White wins!\n\n";
            }
        } else {
            gameMessage = "Game over -- Stalemate\n\n";
        }
    // } else if (matDraw()){
    //     gameMessage = "Game over -- Insufficient Material\n\n";
    // } else if (fiftyMoves()){
    //     gameMessage = "Game over -- 50 move rule\n\n";
    } else if (threeRep()){
        gameMessage = "Game over -- 3 Fold Repitition\n\n";
    } else {
        return false;
    }
    cout << gameMessage;
    setBoard::printBoard(gameBoard, theme, "Classic", true);
    return true;
}

//Checks draw by 3 fold repetition
bool board::threeRep(){
    if (hashMoves.find(key) == hashMoves.end()){
        hashMoves[key] = true;
    } else if (hashMoves.at(key)){
        hashMoves[key] = false;
    } else {
        return true;
    }
    return false;
}

//Look back through boards
void board::reviewGame(string theme[]){
    if(comments && theMove != "Quit"){
        endGame(theme);
    }
    setBoard::cleanBoard(gameBoard);
}

//Resets all variables in class
void board::resetGame(){
    theMove = "None"; 
    startBoard.retBoard(gameBoard); //reset board
    gameMessage= ""; // reset game message
    boards.clear(); //Removes all boards
    hashMoves.clear(); //Removes hashed moves
    startBoard = reset; //Resets starting board
    startBoard.retBoard(gameBoard);
    setBoard::cleanBoard(gameBoard);
}

//Goes through all boards in the game
void board::endGame(string theme[]){
    string command, optLine = "Enter an option: ";
    endGameOpts(optLine);
    int length = boards.size() - 1;
    int pos = length;
    while (getline(cin, command)){
        optLine = "Enter an option: ";
        if (command == "Quit"){
            return;
        } else if(command == "1"){
            pos = 0;
        } else if (command == "2") {
            if (pos > 0){
                pos--;
            } else {
                optLine = "Unable to go back from start of game: ";
            }
        } else if (command == "3") {
            if (pos < length){
                pos++;
            } else {
                optLine = "Unable to go past end of game: ";
            }
        } else if (command == "4") {
            pos = length;
        } else if (command == "5") {
            optLine = "Here is the board: " + boards.at(pos).makeFenString() + "\nEnter a new option: ";
        } else {
            optLine = "Not a legal command, try again: ";
        }
        screen_clear();
        cout << gameMessage;
        piece * printBoard[8][8];
        boards.at(pos).retBoard(printBoard);
        setBoard::printBoard(printBoard, theme, "Classic", true);
        endGameOpts(optLine);
    }
}

//Options menu for looking at boards after game
void board::endGameOpts(string optLine){
    cout << "Review your game - Options\n";
    cout << "Quit\t-\t Return home\n";
    cout << "1 \t-\t Go to game start\n";
    cout << "2 \t-\t Go to previous move\n";
    cout << "3 \t-\t Go to next move\n";
    cout << "4 \t-\t Go to game end\n";
    cout << "5 \t-\t Copy board state for Chess.com\n";
    cout << optLine;
    return;
}


