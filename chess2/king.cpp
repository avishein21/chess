#include "king.h"
#include "checkPiece.h"
#include <iostream>
#include <stdio.h>
using namespace std;

king::king(bool color){
    name = 'K'; 
    if(color){
        player = 1;
    } else {
        player = 0;
    }
    savedPlayer = player;
}

bool king::move(int f1, int f2, int t1, int t2, piece * board[][8], int p){
    (void) p;
    (void) board;
    // Try to castle
    if ((f2 == t2) && (abs(f1 - t1) == 2) && !canCheck(f2, f1, board, player)){
        if (t1 == 2){
            // Queen Side
            return (castleQ && !canCheck(f2, 3, board, player) && 
                    (board[f2][3]->player == 2) && 
                    (board[f2][2]->player == 2) && (board[f2][1]->player == 2));
        } else {
            // King Side
            return (castleK && !canCheck(f2, 5, board, player) && 
                    (board[f2][5]->player == 2) && (board[f2][6]->player == 2));
        }
    }
    return (abs(f1 - t1) <= 1 and abs(f2 - t2) <= 1);
}

// Sees if king can be taken by opposition
bool king::canCheck(int p1, int p2, piece * board[][8], int turn){
    return (pawnCheck(p1, p2, board, turn) || knightCheck(p1, p2, board, turn) || 
            kingCheck(p1, p2, board, turn) || rookCheck(p1, p2, board, turn)   ||
            bishCheck(p1, p2, board, turn));
}

bool king::rookCheck(int p1, int p2, piece * board[][8], int turn){
    return (rbqHelper(p1, p2, board, turn, 1, 0, 'R')  || 
            rbqHelper(p1, p2, board, turn, -1, 0, 'R') ||
            rbqHelper(p1, p2, board, turn, 0, 1, 'R')  ||
            rbqHelper(p1, p2, board, turn, 0, -1, 'R'));
}

bool king::bishCheck(int p1, int p2, piece * board[][8], int turn){
    return  (rbqHelper(p1, p2, board, turn, 1, 1, 'B')   || 
             rbqHelper(p1, p2, board, turn, -1, -1, 'B') ||
             rbqHelper(p1, p2, board, turn, -1, 1, 'B')  ||
             rbqHelper(p1, p2, board, turn, 1, -1, 'B'));
}

bool king::rbqHelper(int p1, int p2, piece * board[][8], int turn, int d1, int d2, char c){
    p1 += d1;
    p2 += d2;
    while ((p2 >= 0) && (p2 < 8) && (p1 >= 0) && (p1 < 8)) {
        piece *temp = board[p1][p2];
        if (temp->player != 2){
            if (((temp->name == 'Q') || (temp->name == c)) and (temp->player != turn)){
                return true;
            }
            return false;
        }
        p1 += d1;
        p2 += d2;
    }
    return false;
}

bool king::pawnCheck(int p1, int p2, piece * board[][8], int turn){
    // White
    if (turn){
        return (pieceCheckHelp(p1 - 1, p2 + 1, board, turn, 'P')) || (pieceCheckHelp(p1 - 1, p2 - 1, board, turn, 'P'));
    // Black
    } else {
        return (pieceCheckHelp(p1 + 1, p2 + 1, board, turn, 'P')) || (pieceCheckHelp(p1 + 1, p2 - 1, board, turn, 'P'));
    }
}

bool king::kingCheck(int p1, int p2, piece * board[][8], int turn){
    for (int i = -1; i < 2; i++){
        for(int j = -1; j < 2; j++){
            if (!((i == 0) && (j == 0)) && (pieceCheckHelp(p1 + i, p2 + j, board, turn, 'K'))){
                return true;
            }
        }
    }
    return false;
}

bool king::knightCheck(int p1, int p2, piece * board[][8], int turn){
    return 
       (pieceCheckHelp(p1 - 1, p2 + 2, board, turn, 'N') || 
        pieceCheckHelp(p1 - 1, p2 - 2, board, turn, 'N') ||
        pieceCheckHelp(p1 + 1, p2 + 2, board, turn, 'N') ||
        pieceCheckHelp(p1 + 1, p2 - 2, board, turn, 'N') ||
        pieceCheckHelp(p1 - 2, p2 + 1, board, turn, 'N') ||
        pieceCheckHelp(p1 - 2, p2 - 1, board, turn, 'N') ||
        pieceCheckHelp(p1 + 2, p2 + 1, board, turn, 'N') ||
        pieceCheckHelp(p1 + 2, p2 - 1, board, turn, 'N'));
}

bool king::pieceCheckHelp(int t1, int t2, piece * board[][8], int turn, char pType){
    if ((t1 < 0) || (t1 > 7) || (t2 < 0) || (t2 > 7)){ return false; } 
    return ((board[t1][t2]->name == pType) and (board[t1][t2]->player != turn));
}

void king::setCastle(bool side){
    if(side) { castleK = false; } else { castleQ = false; }
}
//All moves the king can make
vector <string> king::canMove(int i, int j, bool turn, piece * board[][8]){
    char s1 = 'A' + j;
    char s2 = '8' - i;
    string startPos = string() + s1 + s2 + " ";
    string moveTry;
    vector <string> possibleMoves;
    for (int k = 0; k < 9; k++){
        moveTry =  startPos + char(s1 + (k / 3) - 1) + char(s2 + (k % 3) - 1);
        checkPiece position(board, -1);
        if (position.legal(moveTry, turn, false)){
            possibleMoves.push_back(moveTry);
        }
    }
    return possibleMoves;
}

void king::undoSpace(){
    name = 'K';
    player = savedPlayer;
}

