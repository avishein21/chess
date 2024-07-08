#ifndef _PIECE_H_
#define _PIECE_H_
#include <iostream>
#include <stdio.h>
using namespace std;


class piece
{
    //TODO: Subclasses for rook, knight, bish, king, queen, space
    public: 
        // piece();
        int player;
        char name; 
        
        // virtual bool move(int f1, int f2, int t1, int t2);
        // virtual bool canCheck(int f1, int f2, piece board[][8]);

        //make move func (simple for all but king and pawn)

};

#endif
