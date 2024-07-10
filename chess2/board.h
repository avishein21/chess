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
        void setUpGame(bool Dev, int botColor);
        void gameLoop(string opponent);
        void reviewGame();
        void endGame();
        void endGameOpts(string optLine);
        bool threeRep();
        void resetGame();
        bool matDraw();
        bool playerTurn(checkPiece move);
        int addMat(char c);
        bool checkStop();
        string theme[4]; // Holds colors of pieces
        string mode; // keeps gamemode name
        //General variables for board
        char pieceName; //Letter representing piece being moved
        string theMove = "None"; //String holding current move
        piece *gameBoard[8][8]; //Board where game takes place
        bool turn; //True = White, False = Black
        int initCount; //Amount of pieces on board, to see if capture happened
        int moves; // How many moves until 50 move rule in effect
        int allMoves;//Total moves made
        string gameMessage= ""; //Message for game over
        bool *castle; //Castle array
        bool comments = true; //Turned off for testing
        bool playBot = false; //Is a bot being played?
        bool compTurn = false; //Is it the bot's turn?
        string pessSquare; //Square that can be en passanted
        string key; //Board state fen
        unordered_map<string, bool> hashMoves; //All moves to track 3 fold rep
        fen startBoard;
        fen reset;
        vector <fen> boards; //FENs of all boards (and more info)
};

#endif
