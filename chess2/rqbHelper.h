#ifndef _RQBHELPER_H_
#define _RQBHELPER_H_
#include <iostream>
#include <stdio.h>
#include "piece.h"
using namespace std;


class rqbHelper
{
    public: 
        static vector <string> allRook(int i, int j, bool turn, piece * board[][8]);
        static vector <string> allBish(int i, int j, bool turn, piece * board[][8]);

    private:
        static void rMoveHelper(int i, int j, bool turn, int t1, int t2, 
                        vector <string>& possibleMoves, piece * board[][8]);
      static void bMoveHelper(int i, int j, bool turn, int t1, int t2, 
                        vector <string>& possibleMoves, piece * board[][8]);
};

#endif
