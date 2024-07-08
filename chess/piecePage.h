#ifndef _PIECEPAGE_H_
#define _PIECEPAGE_H_
#include <iostream>
using namespace std;


class piecePage
{
    public:
        void printPage(string colorArr[]);
    private:
        void printPieces();
        void printRow(bool start, string piece, string colors[]);
        void setPieceColor(string colors[], bool pos, char newColor);
        void setSquareColor(string colors[], bool pos, char newColor);
        void printBoard(string colors[]);
        void printSquares();
        void intro(string colorArr[], string newMessage);
        bool checkLine(char type, string line);

};

#endif
