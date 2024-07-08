#include "knight.h"
#include "checkPiece.h"
#include <vector>
#include <iostream>
#include <stdio.h>
using namespace std;

knight::knight(bool color){
    name = 'N'; 
    if(color){
        player = 1;
    } else {
        player = 0;
    }
    savedPlayer = player;
}

bool knight::move(int f1, int f2, int t1, int t2, piece * board[][8], 
                          string p, bool castle[]){
    (void) p;
    (void) castle;
    (void) board;
    if (abs(f1 - t1) == 1){
        if (abs(f2 - t2) != 2){
            return false;
        }
    } else if (abs(f1 - t1) == 2) {
        if (abs(f2 - t2) != 1){
            return false;
        }
    } else {
        return false;
    }
    return true;
}

vector <string> knight::canMove(int i, int j, bool turn, piece * board[][8]){
    vector <string> possibleMoves;
    if(name == '.'){ return possibleMoves; }
    moveHelper(i, j, turn, 1, 2, possibleMoves, board); 
    moveHelper(i, j, turn, 1, -2, possibleMoves, board); 
    moveHelper(i, j, turn, -1, 2, possibleMoves, board);
    moveHelper(i, j, turn, -1, -2, possibleMoves, board);
    moveHelper(i, j, turn, 2, 1, possibleMoves, board);
    moveHelper(i, j, turn, 2, -1, possibleMoves, board); 
    moveHelper(i, j, turn, -2, 1, possibleMoves, board);
    moveHelper(i, j, turn, -2, -1, possibleMoves, board);
    return possibleMoves;
}

void knight::moveHelper(int i, int j, bool turn, int off1, int off2, 
                        vector <string>& possibleMoves, piece * board[][8]){
    bool castle[4] = {false, false, false, false};
    string moveTry;
    char spot = j + 65;
    string initSpot = string(1,spot) + char((8 - i) + 48) + " ";
    moveTry = initSpot + char(spot + off1) + char((8 - i) + 48 + off2);
    checkPiece testKnight(board, "");
    if (testKnight.legal(moveTry, turn, castle, false)){
        possibleMoves.push_back(moveTry);
    }
    return;
}

bool knight::canCheck(int f1, int f2, piece * board[][8]){
    //use to make sure it is not the players own king
    int opp = board[f1][f2]->player;
    if( canCheckHelper(f1 + 1, f2 + 2, board, opp) or
        canCheckHelper(f1 - 1, f2 + 2, board, opp) or
        canCheckHelper(f1 + 1, f2 - 2, board, opp) or
        canCheckHelper(f1 - 1, f2 - 2, board, opp) or
        canCheckHelper(f1 + 2, f2 + 1, board, opp) or
        canCheckHelper(f1 + 2, f2 + 1, board, opp) or
        canCheckHelper(f1 - 2, f2 + 1, board, opp) or
        canCheckHelper(f1 + 2, f2 - 1, board, opp) or
        canCheckHelper(f1 - 2, f2 - 1, board, opp)){
        return true;
    } else {
        return false;
    }
}

bool knight::canCheckHelper(int i, int j, piece * board[][8], int opp){
    if ((i >= 0) and (i <= 7)){
        if ((j >= 0) and (j <= 7)){
            if ((board[i][j]->player != opp) and board[i][j]->name == 'K'){
                return true;
            }
        }
    }
    return false;
}

void knight::undoSpace(){
    name = 'N';
    player = savedPlayer;
}

