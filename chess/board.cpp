#include "board.h"
#include "termfuncs.h"
#include "setBoard.h"
#include "chessBot.h"
#include <fstream>

void board::play(string theme[], string opponent, string gameMode, bool Dev, 
                int botColor){ 
    setUpGame(theme, gameMode, Dev, botColor);
    gameLoop(opponent, theme, gameMode);
    reviewGame(theme);
    resetGame();
}

//Sets all variables
void board::setUpGame(string theme[], string gameMode, bool Dev, int botColor){
    //General booleans for bot/development
    if(Dev){
        comments = false;
    }
    //Get initial position
    if(gameMode == "Custom Position"){
        startBoard = setBoard::customBoard(board, theme);
    }
    startBoard.retBoard(board);
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
    printState(theMove, theme, gameMode);
}

//Main game loop
void board::gameLoop(string opponent, string theme[], string gameMode){
    //Print first board
    while (theMove != "Quit"){
        if(playBot == true and compTurn){
            theMove = botMove(opponent);
        } else {
            getline(cin, theMove);
        }
        if(comments){
            screen_clear();
        }
        checkPiece move(board, pessSquare);
        if (move.check(theMove, turn, castle, compTurn)){
            if (playBot){
                compTurn = !compTurn;
            }
            initCount = pieceCount();
            pieceName = board[7 - (theMove[1] - 49)][theMove[0] - 65].name;
            if (!compTurn and playBot){
                move.makeMove(theMove, board, castle, false, theme, gameMode);
            } else {
                move.makeMove(theMove, board, castle, comments, theme, gameMode);
            }
            pessSquare = move.retPes();
            castleStatus();
            turn = !turn;
            moves++;
            allMoves++;
            fen currFen(board, turn, moves, allMoves, pessSquare, castle);
            key = currFen.retHalfFen();
            boards.push_back(currFen);
            checkPiece checkWin(board, "");
            if (gameOver(checkWin, theme)){
                break;
            }
            printState(moveName(), theme, gameMode);
        } else if(comments){
            printState("Error - " + move.retError(), theme, gameMode);
        }
    }
}

//Look back through boards
void board::reviewGame(string theme[]){
    if(comments){
        if(theMove != "Quit"){
            endGame(theme, gameMessage);
        }
    }
}

//Resets all variables in class
void board::resetGame(){
    theMove = "None"; 
    startBoard.retBoard(board); //reset board
    gameMessage= ""; // reset game message
    boards.clear(); //Removes all boards
    hashMoves.clear(); //Removes hashed moves
    startBoard = reset; //Resets starting board
}

//Updates status on ability to castle
void board::castleStatus(){
    if ((board[0][0].name != 'R') or (board[0][0].player != 0)){
        castle[3] = false;
    }
    if ((board[0][7].name != 'R') or (board[0][7].player != 0)){
        castle[2] = false;
    }
    if ((board[0][4].name != 'K') or (board[0][4].player != 0)){
        castle[2] = false;
        castle[3] = false;
    }
    if ((board[7][0].name != 'R') or (board[7][0].player != 1)){
        castle[1] = false;
    }
    if ((board[7][7].name != 'R') or (board[7][7].player != 1)){
        castle[0] = false;
    }
    if ((board[7][4].name != 'K') or (board[7][4].player != 1)){
        castle[0] = false;
        castle[1] = false;
    }
    return;
}

//Finds total amount of pieces on the board
int board::pieceCount(){
    int total = 0;
    for (int i = 0; i < 8; i++){
       for (int j = 0; j < 8; j++){
            if (board[i][j].player != 2){
                total++;
            }
       }
    }
    return total;
}

//Checks all forms of game over
bool board::gameOver(checkPiece move, string theme[]){
    if (!move.canMove(turn)){
        if(move.canCheck(turn)){
            gameMessage = "Game over -- Checkmate\n";
            if (turn){
                gameMessage += "Black wins!\n\n";
            } else {
                gameMessage += "White wins!\n\n";
            }
        } else {
            gameMessage = "Game over -- Stalemate\n\n";
        }
    } else if (matDraw()){
        gameMessage = "Game over -- Insufficient Material\n\n";
    } else if (fiftyMoves()){
        gameMessage = "Game over -- 50 move rule\n\n";
    } else if (threeRep()){
        gameMessage = "Game over -- 3 Fold Repitition\n\n";
    } else {
        return false;
    }
    cout << gameMessage;
    setBoard::printBoard(board, theme, "Classic", true);
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

//Checks for a draw by not enough mating material
bool board::matDraw(){
    bool blackBN = false;
    bool whiteBN = false;
    for (int i = 0; i < 8; i++){
       for (int j = 0; j < 8; j++)
       {
            if(board[i][j].name == 'Q'){
                return false;
            } else if (board[i][j].name == 'R'){
                return false;
            } else if (board[i][j].name == 'P'){
                return false;
            } else if (board[i][j].name == 'N'){
               if((board[i][j].player == 0) and (not blackBN)){
                    blackBN = true;
               } else if ((board[i][j].player == 1) and (not whiteBN)){
                    whiteBN = true;
               } else {
                return false;
               }
            } else if (board[i][j].name == 'B'){
               if((board[i][j].player == 0) and (not blackBN)){
                    blackBN = true;
               } else if ((board[i][j].player== 1) and (not whiteBN)){
                    whiteBN = true;
               } else {
                return false;
               }
            }
       }
    }
    return true;
}

//Checks for 50 move rule
bool board::fiftyMoves(){
    //moved piece was a pawn or piece taken
    if ((pieceName == 'P') or (initCount != pieceCount())){
        moves = 0;
    }
    //50 move rule occured (50 per person, 100 total)
    if (moves == 100){
        return true;
    }
    return false;
}

//Prints full board with message
void board::printState(string prev, string theme[], string gameMode){
    cout << "Type \"Quit\" to quit\n\nPrevious Move: " << prev << endl << endl;
    setBoard::printBoard(board, theme, gameMode, false);
    if (comments){
        if(turn){
            cout << "\nWhite to move\n";
        } else {
            cout << "\nBlack to move\n";
        }
        cout << "Enter move (from, to): ";
    }
} 

//Creates string describing move
string board::moveName(){
    string name;
    if(pieceName == 'K'){
        name = "King";
    } else if (pieceName == 'Q'){
        name = "Queen";
    } else if (pieceName == 'R'){
        name = "Rook";
    } else if (pieceName == 'B'){
        name = "Bishop";
    } else if (pieceName == 'P'){
        name = "Pawn";
    } else {
        name = "Knight";
    }
    return name + " from " + theMove.substr(0,2) + " to " + theMove.substr(3,2);
}

//Goes through all boards in the game
void board::endGame(string theme[], string endMes){
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
        cout << endMes;
        piece printBoard[8][8];
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

//Picks bot to make move -- CLEAN UP (func even necessary?)
string board::botMove(string opponent){
    chessBot botName;
    if (opponent == "Randall"){
        return botName.randall(turn, board);
    } else if (opponent == "Tammy"){
        return botName.tammy(turn, board);
    } else if (opponent == "Reggie"){
        return botName.reggie(turn, board);
    } else if (opponent == "Parker"){
        return botName.parker(turn, board);
    } else if (opponent == "Francis"){
        return botName.francis(turn, board);
    } else if (opponent == "Gerald"){
        return botName.gerald(turn, board);
    } else {
        cerr << "Bot not yet implemented\n";
        void abort(void);
        return "";
    }
}
