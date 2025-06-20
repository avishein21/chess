#ifndef _PAWN_H_
#define _PAWN_H_
#include <iostream>
#include <stdio.h>
#include "piece.h"
using namespace std;


class pawn
{
    public:
        bool move(int from1, int from2, int to1, int to2, piece board[][8], 
                        int color, string pessSquare);
        vector <string> canMove(int i, int j, bool turn, piece board[][8]);
        bool whiteCanCheck(int f1, int f2, piece board[][8]);
        bool blackCanCheck(int f1, int f2, piece board[][8]);
    private:
        bool whiteMove(int f1, int f2, int t1, int t2, piece board[][8], 
                        string pessSquare);
        bool blackMove(int f1, int f2, int t1, int t2, piece board[][8], 
                        string pessSquare);
        bool checkPessant(int t1, int t2, string pessSquare);
};

#endif
