#ifndef _CHECKPIECE_H_
#define _CHECKPIECE_H_
#include <iostream>
#include <stdio.h>
#include <vector>
#include "pieces/piece.h"
#include "setBoard.h"
using namespace std;


class checkPiece
{
    public:
        //Constructor
        checkPiece(piece * givenB[][8], int pess);

        //Says if a player has ANY move
        bool canMove(bool turn); 

        //Checks if a move is legal
        bool legal(string theMove, bool turn, bool botMove);
        
        //Make move on board and return pessant file if it exists
        int makeMove(string theMove, piece * realBoard[][8], bool comments, 
                        string theme[], string gameMode);

        //Says if any piece can check the king
        bool canCheck(bool turn);

        //Returns error message
        string retError();

    private: 
        // Takes string and turns to locations
        void translateMove(string theMove);
        // Says if legal move for this piece type
        bool pieceMove(piece * test);

        string errMess = ""; //Error message
        int pessSquare = -1;
        piece *board[8][8]; //Local version of board for testing
        int from1, from2, to1, to2; //Locations
        //Normal theme
        string thm[4] = {"\033[1;30m", "\033[0m", "\033[1;100m", "\033[47m"};

        //TODO: add turn, theme, and gamemode variables

        //Move to king?
        void tryCastle(piece *realBoard[][8]);
        
        //Move to pawn?
        void tryPromote(piece *realBoard[][8], bool comments, string theme[], string gameMode);
        piece *getPromoted(piece *realBoard[][8], string theme[], string gameMode, bool player);
};

#endif
