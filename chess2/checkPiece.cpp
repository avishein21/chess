#include "checkPiece.h"
#include "setBoard.h"
#include <iostream>
#include <vector>
#include "termfuncs.h"
#include <regex> 

#include "pieces/knight.h"
#include "pieces/rook.h"
#include "pieces/bish.h"
#include "pieces/queen.h"
#include "pieces/king.h"


using namespace std;

checkPiece::checkPiece(piece * givenB[][8], int pess){
    memcpy(board, givenB, sizeof(board));
    pessSquare = pess;
}

string checkPiece::retError(){
    return errMess;
}

void checkPiece::translateMove(string theMove){
    from1 = theMove[0] - 65;
    from2 = 7 - (theMove[1] - 49);
    to1 = theMove[3] - 65;
    to2 = 7 - (theMove[4] - 49);
}

bool checkPiece::legal(string theMove, bool turn, bool botMove){
    if(botMove){
        return true;
    }
    regex movePattern("[A-H][1-8] [A-H][1-8]");
    if (!regex_match(theMove, movePattern)){
        if((theMove[2] != ' ') or (theMove.length() != 5)){
            errMess = "Not a legal command";
        } else {
            errMess = "Square not on board";
        }
        return false;
    }
    translateMove(theMove);
    if ((from1 == to1) and (from2 == to2)) {
        errMess = "A piece cannot move to its own square";
        return false;
    }
    if (board[from2][from1]->player == 2) {
        errMess = "No piece on this square";
        return false;
    }
    if (board[from2][from1]->player != turn) {
        errMess = "Other player's turn";
        return false;
    }
    piece * fromP = board[from2][from1];
    bool toSpace = (board[to2][to1]->name == '.'); 
    //check legal move for piece
    if (!pieceMove(fromP)){
        return false;
    }
    if (board[to2][to1]->player == fromP->player){
        errMess = "Players cannot take their own pieces";
        return false;
    }
    //Make move on the temporary board
    makeMove(theMove, board, false, thm, "Classic");
    //See if current board state will allows king capture
    if(canCheck(turn)){
        if(!toSpace){
            board[from2][from1]->undoSpace();
        }
        errMess = "Illegal move, king is in check";
        return false;
    }
    //Only revert deletion if taking a piece
    if(!toSpace){
        board[from2][from1]->undoSpace();
    }    
    return true;
}

// Checks if legal move for piece type
bool checkPiece::pieceMove(piece * test){
    //fill in passant
    if (test->move(from1, from2, to1, to2, board, pessSquare)){
        return true;
    } else {
        errMess = "Not a legal " + setBoard::pieceName(test->name) + " move";
        return false;
    }
}

//Make move on real board
int checkPiece::makeMove(string theMove, piece *realBoard[][8], bool comments, 
                            string theme[], string gameMode){
    (void) theme;
    (void) comments;
    (void) gameMode;
    translateMove(theMove);
    // Turn the piece moving to into a space 
    piece *temp = realBoard[to2][to1];
    temp->makeSpace();
    tryCastle(realBoard);
    // If promoting a pawn, switch to new piece before moving
    tryPromote(realBoard, comments, theme, gameMode);
    // Swap positions of piece and space moving to
    realBoard[to2][to1] = realBoard[from2][from1];
    realBoard[from2][from1] = temp;
    // Get en passant square
    return realBoard[to2][to1]->pFile(from2, to2, to1);
}

void checkPiece::tryCastle(piece *realBoard[][8]){
    // if moving the king, it is no longer able to castle
    if((realBoard[from2][from1]->name == 'K') && (abs(from1 - to1) == 2)){
        if(to1 == 6){
            // king side
            piece *space = realBoard[to2][5];
            realBoard[to2][5] = realBoard[to2][7];
            realBoard[to2][7] = space;
        } else {
            // queen side
            piece *space = realBoard[to2][3];
            realBoard[to2][3] = realBoard[to2][0];
            realBoard[to2][0] = space;
        }
    }
}

// Check if pawn on 8th rank, and if so promote (TODO: memory issues)
void checkPiece::tryPromote(piece *realBoard[][8], bool comments, string theme[], string gameMode){
    piece *promote = realBoard[from2][from1];
    // If it's a promoting pawn
    if ((promote->name == 'P') && ((to2 == 0) || (to2 == 7))){
        // Find what to promote to
        if (comments){
            piece *promoted = getPromoted(realBoard, theme, gameMode, promote->player);
            delete realBoard[from2][from1];
            realBoard[from2][from1] = promoted;
        } else {
            // delete realBoard[from2][from1];
            realBoard[from2][from1] = new queen(promote->player);
        }
    }
}

// finds piece to promote to for a pawn (TODO: move to pawn?)
piece *checkPiece::getPromoted(piece *realBoard[][8], string theme[], string gameMode, bool player){
    setBoard print;
    string pieceName;
    cout << "Type \"Quit\" to quit\n\n";
    cout << "Previous Move: Pawn to promotion square\n\n";
    print.printBoard(realBoard, theme, gameMode, false);
    cout << "What piece would you like to promote to (Q, R, N, B): ";
    getline(cin, pieceName);
    screen_clear();
    if (pieceName == "Q"){ return new queen(player); } 
    if (pieceName == "R"){ return new rook(player); } 
    if (pieceName == "B"){ return new bish(player); } 
    if (pieceName == "N"){ return new knight(player); } 
    return getPromoted(realBoard, theme, gameMode, player);
}

// sees if any piece for a player can move (used for check and checkmate)
bool checkPiece::canMove(bool turn){
    piece * temp = board[0][0];
    for (int i = 0; i < 64; i++){
        temp = board[i / 8][i % 8];
        if(!temp->canMove(i / 8, i % 8, turn, board).empty()){
            return true;
        }
    }
    return false;
}

// Sees if king can be taken in current board
bool checkPiece::canCheck(bool turn){
    piece *temp;
    for (int i = 0; i < 64; i++){
        temp = board[i / 8][i % 8];
        // find moved players king, and check if it can be checked
        if ((temp->name == 'K') and (temp->player == turn)){
            return (temp->canCheck(i / 8, i % 8, board, turn));
        }
    }
    return false;
}
