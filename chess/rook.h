#ifndef _ROOK_H_
#define _ROOK_H_
#include <iostream>
#include <stdio.h>
#include "piece.h"
using namespace std;


class rook
{
    public:
        bool move(int from1, int from2, int to1, int to2, piece board[][8]);
        bool canCheck(int f1, int f2, piece board[][8]);
        vector <string> canMove(int i, int j, bool turn, piece board[][8]);

        //Also used in queen
        bool horiz(int from1, int from2, int to1, piece board[][8]);
        bool vert(int from1, int from2, int to2, piece board[][8]);

    private: 
        void canMoveHelper(int i, int j, bool turn, int t1, int t2, 
                        vector <string>& possibleMoves, piece board[][8]);

};

#endif
