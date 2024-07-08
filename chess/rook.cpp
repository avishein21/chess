#include "rook.h"
#include "checkPiece.h"
#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

bool rook::move(int f1, int f2, int t1, int t2, piece board[][8]){
    if (f1 - t1 == 0){
        return vert(f1, f2, t2, board);
    } else if (f2 - t2 == 0) {
        return horiz(f1, f2, t1, board);
    } else {
        return false;
    }
    return true;
}

vector <string> rook::canMove(int i, int j, bool turn, piece board[][8]){
    vector <string> possibleMoves;
    for (int k = 0; k < 8; k++){
        canMoveHelper(i, j, turn, i, k, possibleMoves, board);
        canMoveHelper(i, j, turn, k, j, possibleMoves, board);
    }
    return possibleMoves;
}

void rook::canMoveHelper(int i, int j, bool turn, int t1, int t2, 
                        vector <string>& possibleMoves, piece board[][8]){
    bool castle[4] = {false, false, false, false};
    string moveTry;
    string initSpot = string(1, j + 65) + char((8 - i) + 48) + " ";
    moveTry = initSpot + char(t2 + 65) + char((8 - t1) + 48);
    checkPiece checkMove(board, "");
    if (checkMove.check(moveTry, turn, castle, false)){
        possibleMoves.push_back(moveTry);
    }
    return;
}

//
bool rook::canCheck(int f1, int f2, piece board[][8]){
    int opp = board[f1][f2].player;
    int up = 1, down = 1, left = 1, right = 1;
    // make a function? 
    while(f1 - up >= 0){
        piece test = board[f1 - up][f2];
        if((test.player != opp) and (test.name == 'K')){
            return true;
        } else if ((test.player == opp) or ((test.player != opp) and 
                    (test.name != '.'))){
            break;
        }
        up++;
    }
    while(f1 + down < 8){
        piece test = board[f1 + down][f2];
        if((test.player != opp) and (test.name == 'K')){
            return true;
        } else if ((test.player == opp) or ((test.player != opp) and 
                    (test.name != '.'))){
            break;
        }
        down++;
    }
    while(f2 + right < 8){
        piece test = board[f1][f2 + right];
        if((test.player != opp) and (test.name == 'K')){
            return true;
        } else if ((test.player == opp) or ((test.player != opp) and 
                    (test.name != '.'))){
            break;
        }
        right++;
    }
    while(f2 - left >= 0){
        piece test = board[f1][f2 - left];
        if((test.player != opp) and (test.name == 'K')){
            return true;
        } else if ((test.player == opp) or ((test.player != opp) and 
                    (test.name != '.'))){
            break;
        }
        left++;
    }
    return false;
}

//Checks if the rook can make a vertical move
bool rook::vert(int f1, int f2, int t2, piece board[][8]){
    if (f2 > t2){
        for (int i = 1; i < abs(f2 - t2); i++) {
            if (board[f2 - i][f1].name != '.'){
                return false;
            }
        }
    } else {
        for (int i = 1; i < abs(f2 - t2); i++) {
            if (board[f2 + i][f1].name != '.'){
                return false;
            } 
        }
    }
    return true;
}

//Checks if the rook can make a horizontal move
bool rook::horiz(int f1, int f2, int t1, piece board[][8]){
    if (f1 > t1){
        for (int i = 1; i < abs(f1 - t1); i++) {
            if (board[f2][f1 - i].name != '.'){
                return false;
            } 
        }
    } else {
        for (int i = 1; i < abs(f1 - t1); i++) {
            if (board[f2][f1 + i].name != '.'){
                return false;
            } 
        }
    }
    return true;
}
