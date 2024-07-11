#include "checkPiece.h"
#include "setBoard.h"
#include <iostream>
#include <vector>
#include "termfuncs.h"
#include <regex> 

#include "knight.h"
#include "rook.h"
#include "bish.h"
#include "queen.h"
#include "king.h"


using namespace std;

checkPiece::checkPiece(piece * givenB[][8], string pess){
    memcpy(board, givenB, sizeof(board));
    pessSquare = pess;
}

string checkPiece::retError(){
    return errMess;
}

string checkPiece::retPes(){
    return pessSquare;
}

void checkPiece::translateMove(string theMove){
    from1 = theMove[0] - 65;
    from2 = 7 - (theMove[1] - 49);
    to1 = theMove[3] - 65;
    to2 = 7 - (theMove[4] - 49);
}

bool checkPiece::legal(string theMove, bool turn, bool castle[], bool botMove){
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
    if (!pieceMove(fromP, castle)){
        return false;
    }
    if (board[to2][to1]->player == fromP->player){
        errMess = "Players cannot take their own pieces";
        return false;
    }
    //Make move on the temporary board
    makeMove(theMove, board, castle, false, thm, "Classic");
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
bool checkPiece::pieceMove(piece * test, bool castle[]){
    //fill in passant
    if (test->move(from1, from2, to1, to2, board, "", castle)){
        return true;
    } else {
        errMess = "Not a legal " + setBoard::pieceName(test->name) + " move";
        return false;
    }
}

// void checkPiece::updatePes(string testPes, piece realBoard [][8]){
//     piece space;
//     space.name = '.';
//     space.player = 2;
//     piece checkPiece = realBoard[from2][from1];
//     //Make Pessant
//     if ((testPes == pessSquare)) {
//         if(checkPiece.player == 1){
//             realBoard[to2 + 1][to1] = space;
//         } else {
//             realBoard[to2 - 1][to1] = space;
//         }
//         pessSquare = "";
//     }
//     //Set Passant
//     if (abs(to2 - from2) == 2) {
//         if (checkPiece.player == 1){
//             pessSquare = string(1,('A' + to1)) + string(1,(to2 + '0' - 1));
//         } else {            
//             pessSquare = string(1,('A' + to1)) + string(1,(to2 + '3'));
//         }
//     } else {
//         pessSquare = "";
//     }
// }

//Make move on real board
void checkPiece::makeMove(string theMove, piece *realBoard[][8], bool castle[], 
                            bool comments, string theme[], string gameMode){
    (void) castle;
    (void) theme;
    (void) comments;
    (void) gameMode;
    translateMove(theMove);
    // Turn the piece moving to into a space 
    piece *temp = realBoard[to2][to1];
    temp->makeSpace();
    // If promoting a pawn, switch to new piece before moving
    tryPromote(realBoard, comments, theme, gameMode);
    realBoard[to2][to1] = realBoard[from2][from1];
    // if(!tryCastle(checkPiece, realBoard, castle)){
    // }
    // if (checkPiece.name == 'P'){
    //     updatePes(theMove.substr(3,2), realBoard);
    // } else {
    //     pessSquare = "";
    // }
    realBoard[from2][from1] = temp;
}

// bool checkPiece::tryCastle(piece checkPiece, piece realBoard[][8],
//                             bool castle[]){
//     if(checkPiece.name == 'K'){
//         if((checkPiece.player == 1) and (to1 == 6) and castle[0]){
//             return castleKing(realBoard, 7);
//         } else if((checkPiece.player == 0) and (to1 == 6) and castle[2]){
//             return castleKing(realBoard, 0);
//         } else if((checkPiece.player == 0) and (to1 == 2) and castle[3]){
//             return castleQueen(realBoard, 0);
//         } else if((checkPiece.player == 1) and (to1 == 2) and castle[1]){
//             return castleQueen(realBoard, 7);
//         } else {
//             return false;
//         }
//     }
//     return false;
// }

// bool checkPiece::castleKing(piece realBoard[][8], int side){
//     piece space;
//     space.name = '.';
//     space.player = 2;
//     realBoard[side][5] = realBoard[side][7];
//     realBoard[side][7] = space;
//     realBoard[side][6] = realBoard[side][4];
//     return true;
// }

// bool checkPiece::castleQueen(piece realBoard[][8], int side){
//     piece space;
//     space.name = '.';
//     space.player = 2;
//     realBoard[side][3] = realBoard[side][0];
//     realBoard[side][0] = space;
//     realBoard[side][2] = realBoard[side][4];
//     return true;
// }

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
    piece * temp;
    for (int i = 0; i < 64; i++){
        temp = board[i / 8][i % 8];
        // find moved players king, and check if it can be checked
        if ((temp->name == 'K') and (temp->player == turn)){
            return (temp->canCheck(i / 8, i % 8, board));
        }
    }
    return false;
}
