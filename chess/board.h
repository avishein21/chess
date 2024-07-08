#ifndef _BOARD_H_
#define _BOARD_H_
#include <iostream>
#include "checkPiece.h"
#include "fen.h"
#include <vector>
#include <stdio.h>
#include <unordered_map>

using namespace std;


class board
{
    public:
        //Play the game
        void play(string theme[], string opponent, string gameMode, bool Dev, 
                    int botColor);
    private:
        void setUpGame(string theme[], string gameMode, bool Dev, int botColor);
        void gameLoop(string opponent, string theme[], string gameMode);
        void reviewGame(string theme[]);
        void resetGame();
        string botMove(string opponent);
        void castleStatus();
        bool fiftyMoves();
        int pieceCount();
        bool matDraw();
        bool gameOver(checkPiece move, string theme[]);
        void printState(string prev, string theme[], string gameMode);
        string moveName();
        void endGame(string theme[], string endMes);
        void endGameOpts(string optLine);
        bool threeRep();

        //General variables for board

        char pieceName; //Letter representing piece being moved
        string theMove = "None"; //String holding current move
        piece board[8][8]; //Board where game takes place
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
        vector <fen> boards; //FENs of all boards (and more info)
        unordered_map<string, bool> hashMoves; //All moves to track 3 fold rep
        fen startBoard; //Starting board
        fen reset; //Resets start board at end of game
};

#endif
