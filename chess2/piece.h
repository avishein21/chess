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
        int savedPlayer;
        char name; 
        piece();
        void makeSpace();
        virtual bool move(int f1, int f2, int t1, int t2, piece * board[][8], 
                          string p, bool castle[]);
        virtual bool canCheck(int f1, int f2, piece * board[][8]);
        //make move func? (simple for all but king and pawn)
        virtual vector <string> canMove(int i, int j, bool t, piece * b[][8]);
        virtual void undoSpace();
        virtual ~piece();
};


class Space : public piece {
  public:
    Space();
    bool move(int f1, int f2, int t1, int t2, piece * board[][8], 
                          string p, bool castle[]);
    bool canCheck(int f1, int f2, piece * board[][8]);
    vector <string> canMove(int i, int j, bool turn, 
                                        piece * board[][8]);
    void undoSpace();
};

#endif
