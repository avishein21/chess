#include "king.h"
#include "checkPiece.h"
#include <iostream>
#include <stdio.h>
using namespace std;

bool king::move(int f1, int f2, int t1, int t2, piece board[][8], bool caslte[])
{
    string theMove;
    checkPiece kingCheck(board, "");
    for (int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++){
            piece test = board[t2 + i][t1 + j];
            if ((test.name == 'K') and (test.player != board[f2][f1].player)) {
                return false;
            }
        }
    }
    if (board[t2][t1].name == 'K'){
        return false;
    }
    if (abs(f1 - t1) <= 1 and abs(f2 - t2) <= 1){
        return true;
    } else if (kingCheck.canCheck(board[f2][f1].player)){
        return false;
    } else {
        if (t1 == 6){
            return tryRightCastle(t2, board, caslte);
        } else if (t1 == 2){
            return tryLeftCastle(t2, board,caslte);
            return true;
        } else {
            return false;
        }
    }
}

//All moves the king can make
vector <string> king::canMove(int i, int j, bool turn, piece board[][8]){
    bool castle[4] = {false, false, false, false};
    char spot = j + 65;
    string moveTry;
    vector <string> possibleMoves;
    for (int k = 0; k < 9; k++){
        char trySpot = spot + (k % 3) - 1;
        char trySpot2 = 9 - (i + k/3) + 48;
        char trySpot3 = 8 - (i) + 48;
        moveTry = string(1,spot) + trySpot3 + " " + trySpot + trySpot2;
        checkPiece position(board, "");
        if (position.check(moveTry, turn, castle, false)){
            possibleMoves.push_back(moveTry);
        }
    }
    return possibleMoves;
}

bool king::tryRightCastle(int t2, piece board[][8], bool caslte[]){
    //With white
    if(caslte[0] and (t2 == 7)){
        if((board[7][6].player == 2) and (board[7][5].player == 2)){
            return not throughCheck(board, 7, 5);
        }
        return false;
    //With black
    } else if (caslte[2] and (t2 == 0)){
        if((board[0][6].player == 2) and (board[0][5].player == 2)){
            return not throughCheck(board, 0, 5);
        }
        return false;
    } else {
        return false;
    }
}

bool king::tryLeftCastle(int t2, piece board[][8], bool caslte[]){
    //With white
    if(caslte[1] and (t2 == 7)){
        if((board[7][3].player == 2) and (board[7][2].player == 2)){
            // use "and" again?
            if (board[7][1].player == 2){
                return not throughCheck(board, 7, 3);
            }
        }
        return false;
    //With black
    } else if (caslte[3] and (t2 == 0)){
        if((board[0][3].player == 2) and (board[0][2].player == 2)){
            if (board[0][1].player == 2){
                return not throughCheck(board, 0, 3);
            }
        }
        return false;
    } else {
        return false;
    }
}

bool king::throughCheck(piece board[][8], int row, int col){
    piece tempBoard[8][8];
    for (int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            tempBoard[i][j] = board[i][j];
        }
    }
    tempBoard[row][col].player = tempBoard[row][4].player;
    tempBoard[row][col].name = 'K';
    tempBoard[row][4].name = '.';
    tempBoard[row][4].player = 2;
    checkPiece kingCheck(tempBoard, "");
    return kingCheck.canCheck(tempBoard[row][5].player);
}
