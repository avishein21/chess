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
        bool move(int from1, int from2, int to1, int to2, piece * board[][8], 
                          string p, bool castle[]);
        vector <string> canMove(int i, int j, bool turn, piece * board[][8]);
        void undoSpace();
        //Also in queen
        bool canCheck(int f1, int f2, piece * board[][8]);
        static bool canCheckQ(int f1, int f2, piece * board[][8]);
        static bool rightDiag(int f1, int f2, int t2, piece * board[][8]);
        static bool leftDiag(int f1, int f2, int t2, piece * board[][8]);
    private:
        void moveHelper(int i, int j, bool turn, int t1, int t2, 
                            vector <string>& possibleMoves, piece * board[][8]);
};

#endif
