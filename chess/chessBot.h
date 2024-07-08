#ifndef _CHESSBOT_H_
#define _CHESSBOT_H_
#include <iostream>
#include <vector>
#include <stdio.h>
#include "piece.h"
#include <vector>
using namespace std;

struct numMove
{
    int num;
    string move;
};

class chessBot
{ 
    
    public:
        string randall(bool turn, piece board[][8]);
        string tammy(bool turn, piece board[][8]); 
        string reggie(bool turn, piece board[][8]);
        string parker(bool turn, piece board[][8]);
        string francis(bool turn, piece board[][8]);
        string gerald(bool turn, piece board[][8]);
    private:
        numMove engine(bool turn, piece board[][8], int depth);
        int bestOneMove(bool turn, piece board[][8], string *moveName, 
                        int startComp, int bestCase, int staleMate);
        int updateBestMove(int moveLess, int moveMore, int i, bool turn,
                            vector <string>& holdMove, vector <string> allMove);
        vector <string> allMoves(bool turn, piece board[][8]);
        void addMoves(vector <string>& allMovables, vector <string> pMoves);


};

#endif
