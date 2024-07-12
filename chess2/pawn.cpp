#include "pawn.h"
#include "checkPiece.h"
#include <vector>
#include <iostream>
#include <stdio.h>
#include "termfuncs.h"

using namespace std;

pawn::pawn(bool color){
    name = 'P'; 
    if(color){
        player = 1;
    } else {
        player = 0;
    }
	savedPlayer = player;
}

bool pawn::move(int f1, int f2, int t1, int t2, piece * board[][8], int p){
    if (board[f2][f1]->player){
		// White move
		return pHelper(f1,f2, t1, t2, board, p, -1, 6);
    } else {
		// Black move
		return pHelper(f1,f2, t1, t2, board, p, 1, 1);
	}
}

vector <string> pawn::canMove(int i, int j, bool turn, piece * board[][8]){
    vector <string> possibleMoves;
	if(name == '.'){ return possibleMoves; }
    string moveTry;
    char spot = j + 65;
    string initSpot = string(1,spot) + char((8 - i) + 48) + " ";
	checkPiece pawnMove(board, -1); //TODO: pass in passant square
    for (int k = -1; k < 2; k++){
        if(turn){
            moveTry = initSpot + char(spot + k) + char((8 - i) + 49);
            if (pawnMove.legal(moveTry, turn, false)){
                possibleMoves.push_back(moveTry);
            }
        } else {
            moveTry = initSpot + char(spot + k) + char((8 - i) + 47);
            if (pawnMove.legal(moveTry, turn, false)){
                possibleMoves.push_back(moveTry);
            }
        }
    }
    //try moving 2 spaces up
    if(turn){
        moveTry = initSpot + char(spot) + char((8 - i) + 50);
    } else {
        moveTry = initSpot + char(spot) + char((8 - i) + 46);
    }
    if (pawnMove.legal(moveTry, turn, false)){
        possibleMoves.push_back(moveTry);
    }
    return possibleMoves;  
}

bool pawn::pHelper(int f1, int f2, int t1, int t2, piece *board[][8], 
					int pessSquare, int dir, int startSq){
	// one space
	if (t2 - f2 == dir){
		// Diagonal
		if (abs(f1-t1) == 1){
			// Capture opponent
			if(board[t2][t1]-> player == (board[f2][f1]->player + dir)){
				return true;
			} 
			// Going to pessant file at correct square
			if((t1 == pessSquare) && (t2 == (startSq + (4 * dir)))){
                board[t2 - dir][t1]->makeSpace();
                return true;
            }
            return false;
		} 
		// Straight
		return (((f1-t1) == 0) && (board[t2][t1]-> player == 2));
	}
	// two space (on start, moving 2 up, both spaces empty)
	return ((f2 == startSq) && (t2 == (startSq + 2 * dir)) && (f1 - t1 == 0) && 
			(board[startSq + 2 * dir][t1]-> player == 2) && 
			(board[startSq + dir][t1]-> player == 2));
}

int pawn::pFile(int f2, int t2, int t1){
	if (abs(f2-t2) == 2) { return t1; } else { return -1; }
}

void pawn::undoSpace(){
    name = 'P';
	player = savedPlayer;
}
