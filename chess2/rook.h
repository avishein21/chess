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
        bool move(int from1, int from2, int to1, int to2, piece * board[][8], 
                          string p, bool castle[]);
        vector <string> canMove(int i, int j, bool turn, piece * board[][8]);

        //Also used in queen
        bool canCheck(int f1, int f2, piece * board[][8]);
        static bool canCheckQ(int f1, int f2, piece * board[][8]);
        static bool horiz(int from1, int from2, int to1, piece * board[][8]);
        static bool vert(int from1, int from2, int to2, piece * board[][8]);
        void undoSpace();
    private: 
        void canMoveHelper(int i, int j, bool turn, int t1, int t2, 
                        vector <string>& possibleMoves, piece * board[][8]);

};

#endif