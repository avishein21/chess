#ifndef _CHESSBOT_H_
#define _CHESSBOT_H_
#include <iostream>
#include <vector>
#include <stdio.h>
#include "pieces/piece.h"
#include <vector>
using namespace std;

struct numMove {
    int num;
    string move;
};

class chessBot
{ 
    
    public:
        chessBot(bool t, string opponent);
        string botMove(piece *board[][8]);

    private:
        int depth;
        bool turn;
        string thm[4]; //placeholder for board themes 
        string randall(piece *board[][8]);
        numMove engine(piece *board[][8], bool turn, int depth);

        vector <string> allMoves(piece *board[][8]);
        int boardScore(piece *board[][8]);

        // numMove engine(bool turn, piece board[][8], int depth);
        // int bestOneMove(bool turn, piece board[][8], string *moveName, 
        //                 int startComp, int bestCase, int staleMate);
    //     int updateBestMove(int moveLess, int moveMore, int i, bool turn,
    //                         vector <string>& holdMove, vector <string> allMove);

};

#endif
