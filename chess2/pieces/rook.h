#ifndef _ROOK_H_
#define _ROOK_H_
#include <iostream>
#include <stdio.h>
#include "piece.h"
using namespace std;

class rook : public piece
{
    public:
        rook(bool color);
        bool move(int from1, int from2, int to1, int to2, piece * board[][8], int p);
        vector <string> canMove(int i, int j, bool turn, piece * board[][8]);

        //Also used in queen
        static bool horiz(int from1, int from2, int to1, piece * board[][8]);
        static bool vert(int from1, int from2, int to2, piece * board[][8]);
        void undoSpace();

};

#endif
