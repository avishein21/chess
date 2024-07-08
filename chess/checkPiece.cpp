#include "checkPiece.h"
#include "knight.h"
#include "bish.h"
#include "rook.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"
#include <iostream>
#include <vector>
#include "termfuncs.h"
using namespace std;

checkPiece::checkPiece(piece givenB[][8], string pess){
    for (int i = 0; i < 64; i++){
        board[i / 8][i % 8] = givenB[i / 8][i % 8];
    }
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

bool checkPiece::check(string theMove, bool turn, bool castle[], bool botMove){
    if(botMove){
        return true;
    } 
    if((theMove[2] != ' ') or (theMove.length() != 5)){
        errMess = "Not a legal command";
        return false;
    }
    if ((theMove[0] < 'A' or theMove[0] > 'H') or (theMove[1] < '1' or 
        theMove[1] > '8') or (theMove[3] < 'A' or theMove[3] > 'H') or 
        (theMove[4] < '1' or theMove[4] > '8')) {
        errMess = "Square not on board";
        return false;
    }
    translateMove(theMove);
    if ((from1 == to1) and (from2 == to2)) {
        errMess = "A piece cannot move to its own square";
        return false;
    }
    if (board[from2][from1].player == 2) {
        errMess = "No piece on this square";
        return false;
    }
    if (board[from2][from1].player != turn) {
        errMess = "Other player's turn";
        return false;
    }
    piece fromP = board[from2][from1];
    if (!pieceMove(fromP.name, fromP.player, castle)){
        return false;
    }
    //check legal move for piece
    if (board[to2][to1].player == fromP.player){
        errMess = "Players cannot take their own pieces";
        return false;
    }
    bool temp = isCheck(theMove, turn, castle);
    if(temp){
        errMess = "Illegal move, king is in check";
        return false;
    }
    return true;
}

bool checkPiece::pieceMove(char name, int color, bool castle[]){
    if (name == 'K'){
        king testKing;
        if (not testKing.move(from1, from2, to1, to2, board, castle)){
            errMess = "Not a legal king move";
            return false;
        }
        return true;
    } else if (name == 'Q'){
        queen testQueen;
        if (not testQueen.move(from1, from2, to1, to2, board)){
            errMess = "Not a legal queen move";
            return false;
        }
        return true;
    } else if (name == 'R'){
        rook testRook;
        if(not testRook.move(from1, from2, to1, to2, board)){
            errMess = "Not a legal rook move";
            return false;
        }
        return true;
    } else if (name == 'B'){
        bish testBish;
        if (not testBish.move(from1, from2, to1, to2, board)){
            errMess = "Not a legal bishop move";
            return false;
        }
        return true;
    } else if (name == 'P'){
        pawn testPawn;
        if (not testPawn.move(from1, from2, to1, to2, board, color, pessSquare)){
            errMess = "Not a legal pawn move";
            return false;
        }
        return true;
    } else if (name == 'N'){
        knight testKnight;
        if (not testKnight.move(from1, from2, to1, to2)){
            errMess = "Not a legal knight move";
            return false;
        }
        return true;
    } else {
        errMess = "Not a legal piece";
        return false; 
    }
}

void checkPiece::updatePes(string testPes, piece realBoard [][8]){
    piece space;
    space.name = '.';
    space.player = 2;
    piece checkPiece = realBoard[from2][from1];
    //Make Pessant
    if ((testPes == pessSquare)) {
        if(checkPiece.player == 1){
            realBoard[to2 + 1][to1] = space;
        } else {
            realBoard[to2 - 1][to1] = space;
        }
        pessSquare = "";
    }
    //Set Passant
    if (abs(to2 - from2) == 2) {
        if (checkPiece.player == 1){
            pessSquare = string(1,('A' + to1)) + string(1,(to2 + '0' - 1));
        } else {            
            pessSquare = string(1,('A' + to1)) + string(1,(to2 + '3'));
        }
    } else {
        pessSquare = "";
    }
}

void checkPiece::makeMove(string theMove, piece realBoard[][8], bool castle[], 
                            bool comments, string theme[], string gameMode){
    translateMove(theMove);
    piece checkPiece = realBoard[from2][from1];
    if(!tryCastle(checkPiece, realBoard, castle)){
        if(!tryPromote(checkPiece, realBoard, comments, theme, gameMode)){
            realBoard[to2][to1] = realBoard[from2][from1];
        }
    }
    if (checkPiece.name == 'P'){
        updatePes(theMove.substr(3,2), realBoard);
    } else {
        pessSquare = "";
    }
    piece space;
    space.name = '.';
    space.player = 2;
    realBoard[from2][from1] = space; 
}

bool checkPiece::tryCastle(piece checkPiece, piece realBoard[][8],
                            bool castle[]){
    if(checkPiece.name == 'K'){
        if((checkPiece.player == 1) and (to1 == 6) and castle[0]){
            return castleKing(realBoard, 7);
        } else if((checkPiece.player == 0) and (to1 == 6) and castle[2]){
            return castleKing(realBoard, 0);
        } else if((checkPiece.player == 0) and (to1 == 2) and castle[3]){
            return castleQueen(realBoard, 0);
        } else if((checkPiece.player == 1) and (to1 == 2) and castle[1]){
            return castleQueen(realBoard, 7);
        } else {
            return false;
        }
    }
    return false;
}

bool checkPiece::castleKing(piece realBoard[][8], int side){
    piece space;
    space.name = '.';
    space.player = 2;
    realBoard[side][5] = realBoard[side][7];
    realBoard[side][7] = space;
    realBoard[side][6] = realBoard[side][4];
    return true;
}

bool checkPiece::castleQueen(piece realBoard[][8], int side){
    piece space;
    space.name = '.';
    space.player = 2;
    realBoard[side][3] = realBoard[side][0];
    realBoard[side][0] = space;
    realBoard[side][2] = realBoard[side][4];
    return true;
}

bool checkPiece::tryPromote(piece promote, piece realBoard[][8],
                            bool comments, string theme[], string gameMode){
    if (promote.name == 'P') {
        if (((promote.player == 1) and (to2 == 0)) ||
            ((promote.player == 0) and (to2 == 7))){
            string pieceName;
            setBoard print;
            if (comments){
                cout << "Type \"Quit\" to quit\n\n";
                cout << "Previous Move: Pawn to promotion square\n\n";
                print.printBoard(board, theme, gameMode, false);
                cout << "What piece would you like to promote to (Q, R, N, B): ";
                while(getline(cin, pieceName)){
                    if (pieceName == "Q"){
                        realBoard[to2][to1].name = 'Q';
                        break;
                    } else if (pieceName == "R"){
                        realBoard[to2][to1].name = 'R';
                        break;
                    } else if (pieceName == "B"){
                        realBoard[to2][to1].name = 'B';
                        break;
                    } else if (pieceName == "N"){
                        realBoard[to2][to1].name = 'N';
                        break;
                    } else {                
                        screen_clear();
                        cout << "Type \"Quit\" to quit\n\n";
                        cout << "Previous Move: Pawn to promotion square\n\n";
                        print.printBoard(realBoard, theme, gameMode, false);
                        cout << "Invalid piece, what piece would you like to ";
                        cout << "promote to (Q, R, N, B): ";
                    }
                }
                screen_clear();
            } else {
                realBoard[to2][to1].name = 'Q';
            }
            realBoard[to2][to1].player = promote.player;
            return true;
        }
    }
    return false;
}

bool checkPiece::isCheck(string theMove, bool turn, bool castle[]){
    piece tempBoard[8][8];
    for (int i = 0; i < 64; i++){
            tempBoard[i / 8][i % 8] = board[i / 8][i % 8];
    }
    string theme[1] = {"bogus"};
    string tempPes = pessSquare;
    makeMove(theMove, tempBoard, castle, false, theme, "Classic");
    pessSquare = tempPes;
    checkPiece newBoard(tempBoard, "");
    bool temp = newBoard.canCheck(turn);
    return temp;
}

bool checkPiece::canMove(bool turn){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if(turn == board[i][j].player){
                switch (board[i][j].name){
                    case 'K':
                        king tryKing;
                        if(!tryKing.canMove(i, j, turn, board).empty()){
                            return true;
                        }
                        break;
                    case 'P':
                        pawn tryPawn;
                        if(!tryPawn.canMove(i, j, turn, board).empty()){
                            return true;
                        }
                        break;
                    case 'Q':
                        rook tryQRook;
                        bish tryQbish;
                        if(!tryQRook.canMove(i, j, turn, board).empty() or
                           !tryQbish.canMove(i, j, turn, board).empty()){
                            return true;
                        }
                        break;
                    case 'N':
                        knight tryKnight;
                        if(not tryKnight.canMove(i, j, turn, board).empty()){
                            return true;
                        }
                        break;
                    case 'R':
                        rook tryRook;
                        if(!tryRook.canMove(i, j, turn, board).empty()){
                            return true;
                        }
                        break;
                    case 'B':
                        bish trybish;
                        if(!trybish.canMove(i, j, turn, board).empty()){
                            return true;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }
    return false;
}

bool checkPiece::canCheck(bool turn){
    piece temp;
    for (int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            temp = board[i][j];
            if (temp.player != turn and temp.player != 2){
                switch (temp.name){
                    case 'N': 
                        knight testKnight;
                        if (testKnight.canCheck(i, j, board)){
                            return true;
                        }
                        break;
                    case 'R':
                        rook testRook;
                        if (testRook.canCheck(i, j, board)){
                            return true;
                        }
                        break;
                    case 'B':
                        bish testBish;
                        if (testBish.canCheck(i, j, board)){
                            return true;
                        }
                        break;
                    case 'Q':
                        queen testQueen;
                        if (testQueen.canCheck(i, j, board)){
                            return true;
                        }
                        break;
                    case 'P':
                        pawn testPawn;
                        if(!turn){
                            if(testPawn.whiteCanCheck(i, j, board)){
                                return true;
                            }
                        } else {
                            if(testPawn.blackCanCheck(i, j, board)){
                                return true;
                            }
                        }
                        break;
                    case 'K':
                        break;
                    default:
                        break;
                }
            }
        }
    }
    return false;
}
