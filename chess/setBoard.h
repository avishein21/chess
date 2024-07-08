#ifndef _SETBOARD_H_
#define _SETBOARD_H_
#include <iostream>
#include "piece.h"
#include "fen.h"
using namespace std;


class setBoard
{
    public:
        static void normalBoard(piece board[][8]);
        static fen customBoard(piece board[][8], string colors[]);
        static void printBoard(piece board[][8], string theme[], 
                string gameMode, bool gameOver);
        static int boardPoints(piece board[][8]);
    private:
        static int piecePoints(char pieceName);
        static bool validFen(string test, fen &makeFen);
        static bool validBoard(string boardStr, piece fenBoard[][8]);
        static bool lineVal(string line);
        static void setFullBoard(string boardString, piece board[][8]);
        static void setRow(piece board[][8], int i, int pl);
        static void clearBoard(piece board[][8]);
        static void setOptions(string returnCom, piece useBoard[][8], 
                                string colors[], fen currFen);
        static string deletePiece(string line, piece useBoard[][8]);
        static string addPiece(string line, piece useBoard[][8]);
        static bool placePiece(string line, piece useBoard[][8], string tryName, 
                            int color);
        static void prettyPiece(char Name, string gameMode);
        void validBoard(string);
};

#endif
