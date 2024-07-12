#ifndef _KNIGHT_H_
#define _KNIGHT_H_
#include <iostream>
#include <stdio.h>
#include "piece.h"
using namespace std;

class knight : public piece
{
    public:
        knight(bool color);
        bool move(int from1, int from2, int to1, int to2, piece * board[][8], int p);
        vector <string> canMove(int i, int j, bool turn, piece * board[][8]);
        void undoSpace();
    private: 
        void moveHelper(int i, int j, bool turn, int off1, int off2, 
                        vector <string>& possibleMoves, piece * board[][8]);

};

#endif
