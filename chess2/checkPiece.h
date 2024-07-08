#ifndef _CHECKPIECE_H_
#define _CHECKPIECE_H_
#include <iostream>
#include <stdio.h>
#include <vector>
#include "piece.h"
#include "setBoard.h"
using namespace std;


class checkPiece
{
    public:
        //Constructor
        checkPiece(piece * givenB[][8], string pess);

        //Says if a player has ANY move
        bool canMove(bool turn); 

        //Checks if a move is legal
        bool legal(string theMove, bool turn, bool castle[], bool botMove);
        
        //Make move on board
        void makeMove(string theMove, piece * realBoard[][8], bool castle[], 
                        bool comments, string theme[], string gameMode);

        //Says if any piece can check the king
        bool canCheck(bool turn);

        //Gets total amount of points on board. Move elsewhere? 
        int boardPoints();

        //Returns error message
        string retError();

        //Return pessant Square
        string retPes();
    private: 
        void translateMove(string theMove);
        bool pieceMove(piece * test, bool castle[]);
        int piecePoints(char pieceName);
        void updatePes(string testPes, piece realBoard [][8]);

        string errMess = ""; //Error message
        string pessSquare = "";
        piece * board[8][8]; //Board where game takes place
        int from1, from2, to1, to2; //Locations
        //Normal theme
        string thm[4] = {"\033[1;30m", "\033[0m", "\033[1;100m", "\033[47m"};

        //castle array here?
        //turn here?

    //IF IMPLEMENTING "MOVE" IN PIECE

        //Move to king?
        bool tryCastle(piece checkPiece, piece realBoard[][8], bool castle[]);
        bool castleKing(piece realBoard[][8], int side);
        bool castleQueen(piece realBoard[][8], int side);
        
        //Move to pawn?
        bool tryPromote(piece promote, piece realBoard[][8],
                        bool comments, string theme[], string gameMode);
};

#endif
