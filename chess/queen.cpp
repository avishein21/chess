#include "queen.h"
#include "rook.h"
#include "bish.h"
#include <iostream>
#include <stdio.h>
using namespace std;

bool queen::move(int f1, int f2, int t1, int t2, piece board[][8]){
    if (f1 - t1 == 0){
        rook rookMove;
        return rookMove.vert(f1, f2, t2, board);
    } else if (f2 - t2 == 0) {
        rook rookMove;
        return rookMove.horiz(f1, f2, t1, board);
    } 
    if (abs(f1-t1) == abs(f2 - t2)){
        bish bishMove;
        if (f1 < t1){
            return bishMove.rightDiag(f1, f2, t2, board);
        } else {
            return bishMove.leftDiag(f1, f2, t2, board);
        }
    }
    return false;
}

bool queen::canCheck(int f1, int f2, piece board[][8]){
    rook rookCheck;
    if(rookCheck.canCheck(f1,f2,board)){
        return true;
    }
    bish bishCheck;
    if(bishCheck.canCheck(f1,f2,board)){
        return true;
    }
    return false;
}
