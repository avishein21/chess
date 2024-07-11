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
bool king::move(int f1, int f2, int t1, int t2, piece * board[][8], 
                int p, bool caslte[]){
    (void) p;
    (void) caslte;
    string theMove;
    checkPiece kingCheck(board, -1);
    for (int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            int test2 = t2 + i;
            int test1 = t1 + j;
            if ((test1 >= 0 and test1 < 8) and (test2 >= 0 and test2 < 8)){
                piece * test = board[t2 + i][t1 + j];
                if ((test->name == 'K') and (test->player != board[f2][f1]->player)) {
                    return false;
                }
            }
        }
    }
    if (board[t2][t1]->name == 'K'){
        return false;
    }
    if (abs(f1 - t1) <= 1 and abs(f2 - t2) <= 1){
        return true;
    }
    return false;
    // } else if (kingCheck.canCheck(board[f2][f1]->player)){
    //     return false;
    // } else {
    //     if (t1 == 6){
    //         return tryRightCastle(t2, board, caslte);
    //     } else if (t1 == 2){
    //         return tryLeftCastle(t2, board,caslte);
    //         return true;
    //     } else {
    //         return false;
    //     }
    // }
}

// Sees if king can be taken by opposition
bool king::canCheck(int p1, int p2, piece * board[][8]){
    int turn = board[p1][p2]->player;    
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

//All moves the king can make
vector <string> king::canMove(int i, int j, bool turn, piece * board[][8]){
    bool castle[4] = {false, false, false, false};
    char spot = j + 65;
    string moveTry;
    vector <string> possibleMoves;
    for (int k = 0; k < 9; k++){
        char trySpot = spot + (k % 3) - 1;
        char trySpot2 = 9 - (i + k/3) + 48;
        char trySpot3 = 8 - (i) + 48;
        moveTry = string(1,spot) + trySpot3 + " " + trySpot + trySpot2;
        checkPiece position(board, -1);
        if (position.legal(moveTry, turn, castle, false)){
            possibleMoves.push_back(moveTry);
        }
        
    }
    return possibleMoves;
}

// bool king::tryRightCastle(int t2, piece * board[][8], bool caslte[]){
//     //With white
//     if(caslte[0] and (t2 == 7)){
//         if((board[7][6]->player == 2) and (board[7][5]->player == 2)){
//             return not throughCheck(board, 7, 5);
//         }
//         return false;
//     //With black
//     } else if (caslte[2] and (t2 == 0)){
//         if((board[0][6]->player == 2) and (board[0][5]->player == 2)){
//             return not throughCheck(board, 0, 5);
//         }
//         return false;
//     } else {
//         return false;
//     }
// }

// bool king::tryLeftCastle(int t2, piece * board[][8], bool caslte[]){
//     //With white
//     if(caslte[1] and (t2 == 7)){
//         if((board[7][3]->player == 2) and (board[7][2]->player == 2)){
//             // use "and" again?
//             if (board[7][1]->player == 2){
//                 return not throughCheck(board, 7, 3);
//             }
//         }
//         return false;
//     //With black
//     } else if (caslte[3] and (t2 == 0)){
//         if((board[0][3]->player == 2) and (board[0][2]->player == 2)){
//             if (board[0][1]->player == 2){
//                 return not throughCheck(board, 0, 3);
//             }
//         }
//         return false;
//     } else {
//         return false;
//     }
// }

// bool king::throughCheck(piece * board[][8], int row, int col){
//     piece tempBoard[8][8];
//     for (int i = 0; i < 8; i++){
//         for(int j = 0; j < 8; j++){
//             tempBoard[i][j] = board[i][j];
//         }
//     }
//     tempBoard[row][col].player = tempBoard[row][4].player;
//     tempBoard[row][col].name = 'K';
//     tempBoard[row][4].name = '.';
//     tempBoard[row][4].player = 2;
//     checkPiece kingCheck(tempBoard, "");
//     return kingCheck.canCheck(tempBoard[row][5].player);
// }

void king::undoSpace(){
    name = 'K';
    player = savedPlayer;
}

