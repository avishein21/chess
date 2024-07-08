#ifndef _FEN_H_
#define _FEN_H_
#include <iostream>
#include <stdio.h>
#include "piece.h"
using namespace std;

class fen
{
    public:
        // add board
        fen(piece * board[][8], bool playTurn, int moves50, int moveNum, 
            string pessant, bool castle[]);
        fen(string fenString);
        fen(); //return classic board
        string retHalfFen(); //Get board string
        string makeFenString(); //Get full fen
        //Take board and turn it into current Fen's board
        void retBoard(piece * givenBoard[][8]);
        bool retTurn();
        int retMove50();
        int retMoveNum();
        string retPessant();
        bool* retCastle();
        bool setTurn(string tChar);
        void updateBoard(piece * givenBoard[][8]);
        bool updateCastle(string castles);
        bool updatePessant(string Square);
        bool update50(string num);
        bool updateAllMoves(string num);
        ~fen();

    private:
        bool isNum(string num);
        piece * board[8][8];
        bool turn = true; // True = white, False = Black
        int moves50 = 0;
        int moveNum = 1;
        string pessant = "";
        bool wCastL = true; 
        bool wCastR = true;
        bool bCastL = true; 
        bool bCastR = true;
        string halfFen = "";
        string fullFen = "";
};

#endif
