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

bool pawn::move(int f1, int f2, int t1, int t2, piece * board[][8], 
                          string p, bool castle[]){
	(void) castle;
    if (board[f2][f1]->player){
		return whiteMove(f1,f2, t1, t2, board, p);
    } else {
		return blackMove(f1,f2, t1, t2, board, p);
	}
}

vector <string> pawn::canMove(int i, int j, bool turn, piece * board[][8]){
    vector <string> possibleMoves;
	if(name == '.'){ return possibleMoves; }
    string moveTry;
    bool castle[4] = {false, false, false, false};
    char spot = j + 65;
    string initSpot = string(1,spot) + char((8 - i) + 48) + " ";
	checkPiece pawnMove(board, "");
    for (int k = -1; k < 2; k++){
        if(turn){
            moveTry = initSpot + char(spot + k) + char((8 - i) + 49);
            if (pawnMove.legal(moveTry, turn, castle, false)){
                possibleMoves.push_back(moveTry);
            }
        } else {
            moveTry = initSpot + char(spot + k) + char((8 - i) + 47);
            if (pawnMove.legal(moveTry, turn, castle, false)){
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
    if (pawnMove.legal(moveTry, turn, castle, false)){
        possibleMoves.push_back(moveTry);
    }
    return possibleMoves;  
}

bool pawn::whiteMove(int f1, int f2, int t1, int t2, piece * board[][8], 
					string pessSquare){
	// one space
	if (f2 - t2 == 1){
		if (abs(f1-t1) == 1){
			if(board[t2][t1]-> player == 0){
				return true;
			} else if (checkPessant(t1, t2, pessSquare)){
				return true;
			} else {
				return false;
			}
		} else if ((f1-t1) == 0){
			// check for piece on board in this square
			if(board[t2][t1]-> player == 2){
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	// two space
	} else if (f2 == 6){
		if ((t2 == 4) and (f1 - t1 == 0)){
			if((board[4][t1]-> player == 2) and (board[5][t1]-> player == 2)){
				// Set pessant
				cout << char('A' + t1) << "3 is pessant square\n";
				return true;
			}
		}
		return false;
	} else {
		return false;
	}
	return true;
}

bool pawn::blackMove(int f1, int f2, int t1, int t2, piece * board[][8],
					string pessSquare){
	// one space
	if (t2 - f2 == 1){
		if (abs(t1-f1) == 1){
			if(board[t2][t1]->player == 1){
				return true;
			} else if (checkPessant(t1, t2, pessSquare)){
				return true;
			} else {
				return false;
			}
		} else if ((f1-t1) == 0){
			// check for piece on board in this square
			if(board[t2][t1]->player == 2){
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	// two spaces
	} else if (f2 == 1){
		if ((t2 == 3) and (f1 - t1 == 0)){
			if((board[3][t1]->player == 2) and (board[2][t1]->player == 2)){
				cout << char('A' + t1) << "6 is pessant square\n";
				return true;
			}
		}
		return false;
	} else {
		return false;
	}
}

bool pawn::checkPessant(int t1, int t2, string pessSquare){
	if(pessSquare == ""){
		return false;
	}
	string checkSquare = string(1,t1 + 'A') + string(1, (7 - t2) + '1');
	if (checkSquare == pessSquare){
		return true;
	}
	return false;
}

void pawn::undoSpace(){
    name = 'P';
	player = savedPlayer;
}
