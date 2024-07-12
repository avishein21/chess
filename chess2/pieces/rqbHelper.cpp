#include "rqbHelper.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include "../checkPiece.h"
#include "piece.h"
using namespace std;

vector <string> rqbHelper::allRook(int i, int j, bool turn, piece * board[][8]){
    vector <string> possibleMoves;
    for (int k = 0; k < 8; k++){
        rMoveHelper(i, j, turn, i, k, possibleMoves, board);
        rMoveHelper(i, j, turn, k, j, possibleMoves, board);
    }
    return possibleMoves;
}

vector <string> rqbHelper::allBish(int i, int j, bool turn, piece * board[][8]){
    vector <string> possibleMoves;
    for (int k = 1; k < 8; k++){
        bMoveHelper(i, j, turn, i + k, j + k, possibleMoves, board); 
        bMoveHelper(i, j, turn, i + k, j - k, possibleMoves, board); 
        bMoveHelper(i, j, turn, i - k, j + k, possibleMoves, board);
        bMoveHelper(i, j, turn, i - k, j - k, possibleMoves, board);
    }
    return possibleMoves;
}


void rqbHelper::rMoveHelper(int i, int j, bool turn, int t1, int t2, 
                        vector <string>& possibleMoves, piece * board[][8]){
    string moveTry;
    string initSpot = string(1, j + 65) + char((8 - i) + 48) + " ";
    moveTry = initSpot + char(t2 + 65) + char((8 - t1) + 48);
    checkPiece checkMove(board, -1);
    if (checkMove.legal(moveTry, turn, false)){
        possibleMoves.push_back(moveTry);
    }
    return;
}

void rqbHelper::bMoveHelper(int i, int j, bool turn, int t1, int t2, 
                        vector <string>& possibleMoves, piece * board[][8]){
    string moveTry;
    string initSpot = string(1, j + 65) + char((8 - i) + 48) + " ";
    
    moveTry = initSpot + char(t2 + 65) + char((8 - t1) + 48);
    checkPiece testMove(board, -1);
    if (testMove.legal(moveTry, turn, false)){
        possibleMoves.push_back(moveTry);
    }
    return;
}
