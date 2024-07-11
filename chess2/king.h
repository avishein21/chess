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
        bool canCheck(int f1, int f2, piece * board[][8]);
        bool move(int from1, int from2, int to1, int to2, piece * board[][8],
                    int p, bool castle[]);
        vector <string> canMove(int i, int j, bool turn, piece * board[][8]);
        void undoSpace();
    private:
        bool tryRightCastle(int t2, piece * board[][8], bool caslte[]);
        bool tryLeftCastle(int t2, piece * board[][8], bool caslte[]);
        bool throughCheck(piece * board[][8], int row, int col);
        bool knightCheck(int p1, int p2, piece * board[][8], int turn);
        bool pawnCheck(int p1, int p2, piece * board[][8], int turn);
        bool rookCheck(int p1, int p2, piece * board[][8], int turn);
        bool bishCheck(int p1, int p2, piece * board[][8], int turn);
        bool kingCheck(int p1, int p2, piece * board[][8], int turn);
        bool pieceCheckHelp(int p1, int p2, piece * board[][8], int turn, char pType);
        bool rbqHelper(int p1, int p2, piece * board[][8], int turn, int d1, int d2, char c);

};

#endif
