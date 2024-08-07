#ifndef _BOARD_H_
#define _BOARD_H_
#include <iostream>
#include "checkPiece.h"
#include <vector>
#include <stdio.h>
#include <unordered_map>
#include "fen.h"

using namespace std;


class board
{
    public:
        //Play the game
        void play(string theme[], string opponent, string gameMode, bool Dev, 
                    int botColor);
    private:
        bool gameOver(checkPiece move);
        void printState(string prev);
        string moveName();
        void setUpGame(int botColor, string opp);
        void gameLoop(string opponent);
        void startCastle();
        void startCastleHelper(int row, int player);

        void updateCastle(piece *pieceName);
        void reviewGame();
        void endGame();
        void endGameOpts(string optLine);
        bool threeRep();
        void resetGame();
        bool matDraw();
        bool playerTurn(checkPiece move);
        int addMat(char c);
        bool checkStop();

        // Holds colors of pieces (default here)
        string theme[4] = {"\033[1;30m", "\033[0m", "\033[1;100m", "\033[47m"}; 
        string mode; // keeps gamemode name
        piece *movedP; //Letter representing piece being moved
        string theMove = "None"; //String holding current move
        piece *gameBoard[8][8]; //Board where game takes place
        bool turn; //True = White, False = Black
        int moves; // How many moves until 50 move rule in effect
        int allMoves;//Total moves made
        string gameMessage= ""; //Message for game over
        bool castle[4]; //Castle array: White Queen/King, Black Queen/King
        bool comments; //Turned off for testing
        bool playBot = false; //Is a bot being played?
        bool compTurn = false; //Is it the bot's turn?
        int pessSquare = -1; //Column that can be en passanted
        string key; //Board state fen
        fen startBoard;
        fen reset;
        unordered_map<string, bool> hashMoves; //All moves to track 3 fold rep
        vector <fen> boards; //FENs of all boards (and more info)
        // TODO: variables for 2 king positions
};

#endif
