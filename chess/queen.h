#ifndef _QUEEN_H_
#define _QUEEN_H_
#include <iostream>
#include <stdio.h>
#include "piece.h"
using namespace std;


class queen
{
    public:
        bool move(int from1, int from2, int to1, int to2, piece board[][8]);
        bool canCheck(int f1, int f2, piece board[][8]);


};

#endif
