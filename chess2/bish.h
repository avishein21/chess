#ifndef _BISH_H_
#define _BISH_H_
#include <iostream>
#include <stdio.h>
#include "piece.h"
using namespace std;

class bish : public piece
{
    public:
        bish(bool color);
        bool move(int from1, int from2, int to1, int to2, piece * board[][8], int p);
        vector <string> canMove(int i, int j, bool turn, piece * board[][8]);
        void undoSpace();
        static bool rightDiag(int f1, int f2, int t2, piece * board[][8]);
        static bool leftDiag(int f1, int f2, int t2, piece * board[][8]);
};

#endif
