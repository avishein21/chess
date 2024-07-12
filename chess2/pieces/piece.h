#ifndef _PIECE_H_
#define _PIECE_H_
#include <iostream>
#include <stdio.h>
using namespace std;


class piece
{
    public: 
        // piece();
        int player;
        int savedPlayer;
        char name; 
        piece();
        void makeSpace();
        virtual int pFile(int f2, int t2, int t1);
        virtual bool move(int f1, int f2, int t1, int t2, piece * board[][8], int p);
        virtual bool canCheck(int f1, int f2, piece * board[][8], int turn);
        virtual vector <string> canMove(int i, int j, bool t, piece * b[][8]);
        virtual void undoSpace();
        // if true then cannot castle king, else cannot castle queen
        virtual void setCastle(bool side); 
        virtual ~piece();
};


class Space : public piece {
  public:
    Space();
    bool move(int f1, int f2, int t1, int t2, piece * board[][8], int p);
    bool canCheck(int f1, int f2, piece * board[][8], int turn);
    vector <string> canMove(int i, int j, bool turn, 
                                        piece * board[][8]);
    void undoSpace();
};

#endif
