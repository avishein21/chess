#ifndef _KING_H_
#define _KING_H_
#include <iostream>
#include <stdio.h>
#include "piece.h"
using namespace std;


class king
{
    public:
        bool move(int from1, int from2, int to1, int to2, piece board[][8],
                    bool castle[]);
        vector <string> canMove(int i, int j, bool turn, piece board[][8]);

    private:
        bool tryRightCastle(int t2, piece board[][8], bool caslte[]);
        bool tryLeftCastle(int t2, piece board[][8], bool caslte[]);
        bool throughCheck(piece board[][8], int row, int col);


};

#endif
