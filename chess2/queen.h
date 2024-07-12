#ifndef _QUEEN_H_
#define _QUEEN_H_
#include <iostream>
#include <stdio.h>
#include "piece.h"
using namespace std;

class queen : public piece
{
    public:
        queen(bool color);
        bool move(int from1, int from2, int to1, int to2, piece * board[][8], int p);
        vector <string> canMove(int i, int j, bool turn, piece * board[][8]);
        void undoSpace();

};

#endif
