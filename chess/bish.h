#ifndef _BISH_H_
#define _BISH_H_
#include <iostream>
#include <stdio.h>
#include "piece.h"
using namespace std;


class bish
{
    public:
        bool move(int from1, int from2, int to1, int to2, piece board[][8]);
        bool rightDiag(int f1, int f2, int t2, piece board[][8]);
        bool leftDiag(int f1, int f2, int t2, piece board[][8]);
        bool canCheck(int f1, int f2, piece board[][8]);
        vector <string> canMove(int i, int j, bool turn, piece board[][8]);
        void moveHelper(int i, int j, bool turn, int t1, int t2, 
                            vector <string>& possibleMoves, piece board[][8]);
};

#endif
