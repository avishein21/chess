#include "queen.h"
#include "rook.h"
#include "bish.h"
#include <iostream>
#include <stdio.h>
#include "rqbHelper.h"
using namespace std;

queen::queen(bool color){
    name = 'Q'; 
    if(color){
        player = 1;
    } else {
        player = 0;
    }
    savedPlayer = player;
}

bool queen::move(int f1, int f2, int t1, int t2, piece * board[][8], 
                          string p, bool castle[]){
    (void) p;
    (void) castle;
    if (f1 - t1 == 0){
        return rook::vert(f1, f2, t2, board);
    } else if (f2 - t2 == 0) {
        return rook::horiz(f1, f2, t1, board);
    } 
    if (abs(f1-t1) == abs(f2 - t2)){
        if (f1 < t1){
            return bish::rightDiag(f1, f2, t2, board);
        } else {
            return bish::leftDiag(f1, f2, t2, board);
        }
    }
    return false;
}

bool queen::canCheck(int f1, int f2, piece * board[][8]){
    return (rook::canCheckQ(f1, f2, board) or bish::canCheckQ(f1, f2, board));
}

vector <string> queen::canMove(int i, int j, bool turn, piece * board[][8]){
    vector <string> allMoves;
	if(name == '.'){ return allMoves; }
    vector <string> bMoves;
    allMoves = rqbHelper::allRook(i, j, turn, board);
    bMoves = rqbHelper::allBish(i, j, turn, board);
    allMoves.insert(allMoves.end(), bMoves.begin(), bMoves.end());
    return allMoves;
}

void queen::undoSpace(){
    name = 'Q';
    player = savedPlayer;
}

