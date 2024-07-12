#ifndef _KING_H_
#define _KING_H_
#include <iostream>
#include <stdio.h>
#include "piece.h"
using namespace std;


class king : public piece
{
    public:
        king(bool color);
        bool canCheck(int f1, int f2, piece * board[][8], int turn);
        bool move(int from1, int from2, int to1, int to2, piece * board[][8], int p);
        vector <string> canMove(int i, int j, bool turn, piece * board[][8]);
        void undoSpace();
        void setCastle(bool side);
        void noKingCastle();
    private:
        // Functions to see if king is in check
        bool knightCheck(int p1, int p2, piece * board[][8], int turn);
        bool pawnCheck(int p1, int p2, piece * board[][8], int turn);
        bool rookCheck(int p1, int p2, piece * board[][8], int turn);
        bool bishCheck(int p1, int p2, piece * board[][8], int turn);
        bool kingCheck(int p1, int p2, piece * board[][8], int turn);
        bool pieceCheckHelp(int p1, int p2, piece * board[][8], int turn, char pType);
        bool rbqHelper(int p1, int p2, piece * board[][8], int turn, int d1, int d2, char c);
        bool kingSide(int row, piece *board[][8]);
        bool castleK = true;
        bool castleQ = true;

};

#endif
