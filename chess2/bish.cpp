#include "bish.h"
#include <vector>
#include <iostream>
#include <stdio.h>
#include "checkPiece.h"
using namespace std;

bish::bish(bool color){
    name = 'B'; 
    if(color){
        player = 1;
    } else {
        player = 0;
    }
    savedPlayer = player;
}

bool bish::move(int f1, int f2, int t1, int t2, piece * board[][8], 
                          string p, bool castle[]){
    (void) p;
    (void) castle;
    if (abs(f1-t1) == abs(f2 - t2)){
        if (f1 < t1){
            return rightDiag(f1, f2, t2, board);
        } else {
            return leftDiag(f1, f2, t2, board);
        }
    } else {
        return false;
    }
    return true;
}

vector <string> bish::canMove(int i, int j, bool turn, piece * board[][8]){
    vector <string> possibleMoves;
	if(name == '.'){ return possibleMoves; }
    for (int k = 1; k < 8; k++){
        moveHelper(i, j, turn, i + k, j + k, possibleMoves, board); 
        moveHelper(i, j, turn, i + k, j - k, possibleMoves, board); 
        moveHelper(i, j, turn, i - k, j + k, possibleMoves, board);
        moveHelper(i, j, turn, i - k, j - k, possibleMoves, board);
    }
    return possibleMoves;
}

void bish::moveHelper(int i, int j, bool turn, int t1, int t2, 
                        vector <string>& possibleMoves, piece * board[][8]){
        bool castle[4] = {false, false, false, false};
    string moveTry;
    string initSpot = string(1, j + 65) + char((8 - i) + 48) + " ";
    
    moveTry = initSpot + char(t2 + 65) + char((8 - t1) + 48);
    checkPiece testMove(board, "");
    if (testMove.legal(moveTry, turn, castle, false)){
        possibleMoves.push_back(moveTry);
    }
    return;
}

bool bish::rightDiag(int f1, int f2, int t2, piece * board[][8]){
        //moving up 
    if (f2 > t2){
        for (int i = 1; i < abs(f2 - t2); i++) {
            if (board[f2 - i][f1 + i]->name != '.'){
                return false;
            }
        }
    //moving down
    } else {
        for (int i = 1; i < abs(f2 - t2); i++) {
            if (board[f2 + i][f1 + i]->name != '.'){
                return false;
            }
        }
    }
    return true;
}

bool bish::leftDiag(int f1, int f2, int t2, piece * board[][8]){
    if (f2 > t2){
        //moving up
        for (int i = 1; i < abs(f2 - t2); i++) {
            if (board[f2 - i][f1 - i]->name != '.'){
                return false;
            }
        }
    } else {
        for (int i = 1; i < abs(f2 - t2); i++) {
            if (board[f2 + i][f1 - i]->name != '.'){
                return false;
            }
        }
    }
    return true;
}

bool bish::canCheck(int f1, int f2, piece * board[][8]){
    return bish::canCheckQ(f1, f2, board);
}

bool bish::canCheckQ(int f1, int f2, piece * board[][8]){
    int opp = board[f1][f2]->player;
    int i = 1;
    while((f1 + i) < 8 and (f2 + i) < 8){
        piece * test = board[f1 + i][f2 + i];
        if((test->player != opp) and (test->name == 'K')){
            return true;
        } else if ((test->player == opp) or ((test->player != opp) and 
                    (test->name != '.'))){
            break;
        }
        i++;
    }
    i = 1;
    while((f1 - i) >= 0 and (f2 + i) < 8){
        piece * test = board[f1 - i][f2 + i];
        if((test->player != opp) and (test->name == 'K')){
            return true;
        } else if ((test->player == opp) or ((test->player != opp) and 
                    (test->name != '.'))){
            break;
        }
        i++;
    }
    i = 1;
    while((f1 + i) < 8 and (f2 - i) >= 0){
        piece * test = board[f1 + i][f2 - i];
        if((test->player != opp) and (test->name == 'K')){
            return true;
        } else if ((test->player == opp) or ((test->player != opp) and 
                    (test->name != '.'))){
            break;
        }
        i++;
    }
    i = 1;
    while((f1 - i) >=0 and (f2 - i) >= 0){
        piece * test = board[f1 - i][f2 - i];
        if((test->player != opp) and (test->name == 'K')){
            return true;
        } else if ((test->player == opp) or ((test->player != opp) and 
                    (test->name != '.'))){
            break;
        }
        i++;
    }
    return false;
}

void bish::undoSpace(){
    name = 'B';
    player = savedPlayer;
}

