#include "board.h"
#include "termfuncs.h"
#include "setBoard.h"
#include <fstream>
#include <vector>
#include "chessBot.h"

void board::play(string givenTheme[], string opponent, string gameMode, bool Dev, 
                int botColor){
    // Set variables for this board
    for (int i = 0; i < 4; i++){ theme[i] = givenTheme[i]; }
    mode = gameMode;
    comments = !Dev;
    // Play game
    setUpGame(botColor, opponent);
    gameLoop(opponent);
    reviewGame();
    resetGame();
}

//Sets multiple variables for game
void board::setUpGame(int botColor, string opponent){
    (void) opponent;
    //Get initial position
    if(mode == "Custom Position"){
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
    pessSquare = int (startBoard.retPessant()[0] - 'A');
    turn = startBoard.retTurn();
    for (int i = 0; i < 4; i++){ castle[i] = startBoard.retCastle()[i]; }
    // Overrule initial castle rights if rooks and kings on wrong squares
    startCastle();

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
    printState(theMove);
}

//Main Game Loop
void board::gameLoop(string opponent){
    chessBot robot(compTurn, opponent);
    // Get first move
    if (compTurn){
        theMove = robot.botMove(gameBoard);
    } else {
        getline(cin, theMove);
    }
    while (!checkStop()){
        screen_clear();
        // Check if player wants to stop game
        checkPiece move(gameBoard, pessSquare);
        // Make move if possible
        if (playerTurn(move)) { break; }
        // Get new move
        if (compTurn){
            theMove = robot.botMove(gameBoard);
        } else {
            getline(cin, theMove);
        }
    }
}

// Checks if player wants to stop game
bool board::checkStop(){
    if (theMove == "Quit"){
        return true;
    } else if (theMove == "Resign"){
        if (turn){
            cout << "Game Over White Resigned\n\n";
        } else {
            cout << "Game Over Black Resigned\n\n";
        }
        setBoard::printBoard(gameBoard, theme, "Classic", true);
        endGame();
        theMove = "Quit";
        return true;
    }
    return false;
}

// Makes move, and returns true if game is over, false otherwise
bool board::playerTurn(checkPiece move){
    if (move.legal(theMove, turn, compTurn)){
        if (playBot){
            compTurn = !compTurn;
        }
        movedP = gameBoard[7 - (theMove[1] - 49)][theMove[0] - 65];
        bool captured = (gameBoard[7 - (theMove[4] - 49)][theMove[3] - 65]->player != 2);
        // make move
        pessSquare = move.makeMove(theMove, gameBoard, comments, theme, mode);
        // count move (both halfmoves and total)
        if (captured || (movedP->name == 'P')){ moves = 0; } else { moves++; }
        allMoves++;
        // Update castle status
        updateCastle(movedP);
        // Switch turn
        turn = !turn;
        // Create move name for printing
        string moveName = setBoard::pieceName(movedP->name) + " from ";
        moveName += theMove.substr(0,2) + " to " + theMove.substr(3,2);
        // Create Fen for current position
        fen currFen(gameBoard, turn, moves, allMoves, "", castle);
        // Add board to list of moves
        key = currFen.retHalfFen();
        // Check if game is over
        checkPiece checkWin(gameBoard, pessSquare);
        boards.push_back(currFen);
        if (gameOver(checkWin)){ return true; }
        printState(moveName);
    } else {
        printState("Error - " + move.retError());
    }
    return false;
}

//Prints full board with message
void board::printState(string prev){
    cout << "Type \"Quit\" to quit, or \"Resign\" to resign\n\nPrevious Move: " << prev << endl << endl;
    setBoard::printBoard(gameBoard, theme, mode, false);
    if (comments){
        if(turn){
            cout << "\nWhite to move\n";
        } else {
            cout << "\nBlack to move\n";
        }
        cout << "Enter move (from, to): ";
    }
} 

void board::startCastle(){
    for (int i = 0; i < 64; i++){
        // All pieces not on king starting spots cannot castle
        if (!((i == 4) || (i == 60))){
            gameBoard[i / 8][i % 8]->setCastle(true);
            gameBoard[i / 8][i % 8]->setCastle(false);
        }
    }
    startCastleHelper(7, 1); // White king
    startCastleHelper(0, 0); // Black king
}

void board::startCastleHelper(int row, int player){
    if (gameBoard[row][4]->name =='K'){
        // Wrong king, no castling
        if (gameBoard[row][4]->player != 1){
            gameBoard[row][4]->setCastle(true);
            gameBoard[row][4]->setCastle(false);
            castle[2 - (2 * player)] = false;
            castle[3 - (2 * player)] = false;
        } else if ((gameBoard[row][0]->player != 1) || (gameBoard[row][0]->name != 'R')){
            // Castle Queenside no Rook
            gameBoard[row][4]->setCastle(false);
            castle[3 - (2 * player)] = false;
        } else if ((gameBoard[row][7]->player != 1) || (gameBoard[row][7]->name != 'R')){
            // Castle Kingside no Rook
            gameBoard[row][4]->setCastle(true);
            castle[2 - (2 * player)] = false;
        }
    }
}

// Update king pieces to say if they can castle, and local castle array
void board::updateCastle(piece *p){
    // if king moved, it cannot castle, otherwise this does nothing
    p->setCastle(true);
    p->setCastle(false);
    // check if correct rooks are still in corners, and update kings accordingly
    // White
    if (gameBoard[7][0]->player != 1){
        gameBoard[7][4]->setCastle(false);
        castle[0] = false;
    }
    if (gameBoard[7][7]->player != 1){
        gameBoard[7][4]->setCastle(true);
        castle[1] = false;
    }
    // Black
    if (gameBoard[0][0]->player != 0){
        gameBoard[0][4]->setCastle(false);
        castle[2] = false;
    }
    if (gameBoard[0][7]->player != 0){
        gameBoard[0][4]->setCastle(true);
        castle[3] = false;
    }
}

//Checks all forms of game over
bool board::gameOver(checkPiece checkWin){
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
    } else if (matDraw()){
        gameMessage = "Game over -- Insufficient Material\n\n";
    } else if (moves == 100){
        gameMessage = "Game over -- 50 move rule\n\n";
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

// Checks if there's enough material remaining on board for mate
bool board::matDraw(){
    int wMat = 0;
    int bMat = 0;
    for (int i = 0; i < 64; i++){
        piece *p = gameBoard[i / 8][i % 8];
        if(p->player == 0){
            bMat += addMat(p->name);
        } else if (p->player == 1){
            wMat += addMat(p->name);
        }
        if ((bMat > 2) || (wMat > 2)){
            return false;
        }
    }
    return true;
}

// Helper from matDraw
int board::addMat(char c){
    if (c == 'N'){
        return 1;
    } else if (c == 'B'){
        return 2;
    } else if (!(c == 'K')){
        return 5;
    } else {
        return 0;
    }
}

//Look back through boards
void board::reviewGame(){
    if(comments && theMove != "Quit"){
        endGame();
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
void board::endGame(){
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
