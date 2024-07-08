#ifndef _SETBOARD_H_
#define _SETBOARD_H_
#include <iostream>
#include "piece.h"
#include "fen.h"
using namespace std;


class setBoard
{
    public:
        static void normalBoard(piece * board[][8]);
        static void printBoard(piece * board[][8], string theme[], 
                string gameMode, bool gameOver);
        static int boardPoints(piece * board[][8]);
        static string pieceName(char pieceName);
        static void cleanBoard(piece * board[][8]);
        static void setOptions(string returnCom, piece * useBoard[][8], 
                            string colors[], fen currFen);
        static fen customBoard(piece * useBoard[][8], string colors[]);
        static string deletePiece(string line, piece * useBoard[][8]);
        static string addPiece(string line, piece * useBoard[][8]);
        static piece * makePiece(char let, bool color);
        static bool validFen(string testString, fen &makeFen);

    private:
        static bool delFen(fen deleting);
        static bool lineVal(string testString);
        static void setFullBoard(string boardString, piece * useBoard[][8]);

        static bool placePiece(string line, piece * useBoard[][8],
                                string tryName, int color);
        static bool validBoard(string boardStr);
        static void clearBoard(piece * useBoard[][8]);
        static int piecePoints(char pieceName);        
        static void prettyPiece(char Name, string gameMode);
};

#endif
