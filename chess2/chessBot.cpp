#include "checkPiece.h"
#include <vector>
#include "chessBot.h"
#include <cstdlib>
#include <thread>
#include "setBoard.h"

const int CHECKMATE = 100000;
const int STALEMATE = -10000;

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds


chessBot::chessBot(bool t, string opp){
    if (opp == "Randall"){ depth = 0; } 
    else if (opp == "Tammy"){  depth = 1; } 
    else { depth = 2; }
    turn = t;
}

string chessBot::botMove(piece *board[][8]){
    if (depth == 0) { return randall(board); } 
    else { return engine(board, turn, depth).move; }
}

// Gets a random move from the all moves vector
string chessBot::randall(piece *board[][8]){
    sleep_until(system_clock::now() + seconds(1));
    srand(time(0));
    vector <string> allMovables = allMoves(board);
    int move = rand() % allMovables.size();
    return allMovables.at(move);
}

// Gets a move and its associated value for given depth
numMove chessBot::engine(piece *board[][8], bool t, int deep){
    // get all moves
    vector <string> allMovables = allMoves(board);
    vector <numMove> moveRatings;
    // -1 for black, 1 for white
    int mult = t * 2 - 1;

    // All future moves and their values
    vector<string>::iterator it;
    for (it = allMovables.begin(); it != allMovables.end(); it++) {
        // make board copy and make move on copy
        piece *copyBoard[8][8];
        setBoard::copyBoard(board, copyBoard);
        checkPiece copiedMove(copyBoard, -1);
        // make move on board
        copiedMove.makeMove(*it, copyBoard, false, thm, "");
        // if checkmate or stalemate, return move
        if (!copiedMove.canMove(!t)){
            if (copiedMove.canCheck(!t)){
                struct numMove tempMove = { CHECKMATE, *it};
                return tempMove;
            } else {
                struct numMove tempMove = { STALEMATE, *it};
                moveRatings.push_back(tempMove);
            }
        } else {
            // TODO: alpha beta here
            if (deep == 1){
                // TODO: if stalemate, points = STALEMATE
                int points = setBoard::boardPoints(copyBoard) * mult;
                struct numMove tempMove = { points, *it};
                moveRatings.push_back(tempMove);
            } else {
                // see what oppenent gives
                numMove oppMove = engine(copyBoard, !t, deep - 1);
                oppMove.num *= -1;
                moveRatings.push_back(oppMove);
            }
        }
    }
    // get max value
    int maxVal = CHECKMATE * -1;
    for (int i = 0; i < (int) moveRatings.size(); i++){
        int tryMax = moveRatings[i].num;
        if (tryMax > maxVal){ maxVal = tryMax; }
    }
    allMovables.clear();
    // get all moves of max value
    for (int i = 0; i < (int) moveRatings.size(); i++){
        if(moveRatings[i].num == maxVal){ allMovables.emplace_back(moveRatings[i].move); }
    }
    int move = rand() % allMovables.size();
    struct numMove ret = { maxVal, allMovables.at(move)};
    return ret;
}

vector <string> chessBot::allMoves(piece *board[][8]){
    vector <string> pMoves;
    vector <string> allMovables;
    for (int i = 0; i < 64; i++){
        piece *temp =  board[i / 8][i % 8];
        // get moves for a piece
        if (temp->player == turn){
            pMoves = temp->canMove(i / 8, i % 8, turn, board);
        }
        // append moves
        allMovables.insert(allMovables.end(), pMoves.begin(), pMoves.end());
        pMoves.clear();
    }
    return allMovables;
}

// numMove chessBot::engine(bool turn, piece board[][8], int depth){
//     checkPiece testPiece(board, "");
//     bool castle[] = {false, false, false, false};
//     int worstCase = INT_MAX;
//     int bestCase = INT_MIN;
//     int staleMate = INT16_MAX;
//     numMove returnMove;
//     string bestMove;
//     vector <numMove> possibilities;
//     vector <string> allMovables = allMoves(turn, board);
//     int length = allMovables.size();
//     if (turn){
//         worstCase = INT_MIN;
//         bestCase = INT_MAX;
//         staleMate = INT16_MIN;
//     }
//     //test mate in 1
//     int boardEval = bestOneMove(turn, board, &bestMove, worstCase, bestCase, 
//                                 staleMate);   
//     if(boardEval == bestCase){
//         returnMove.move = bestMove;
//         returnMove.num = boardEval;
//         return returnMove;
//     }
//     for (int i = 0; i < length; i++){
//         piece tempBoard[8][8];
//         for(int j = 0; j < 64; j++){
//             tempBoard[j%8][j/8] = board[j%8][j/8];
//         }
//         string theme[1] = {"bogus"};
//         testPiece.makeMove(allMovables.at(i), tempBoard, castle, false, theme, "Classic");
//         if(depth == 1){
//             returnMove.num = bestOneMove(!turn, tempBoard, &bestMove, bestCase, worstCase, staleMate);       
//         } else {
//             returnMove = engine(!turn, tempBoard, depth - 1);
//         }
//         returnMove.move = allMovables.at(i);
//         if(possibilities.empty()){
//             possibilities.push_back(returnMove);
//         } else if (possibilities.at(0).num == returnMove.num){
//             possibilities.push_back(returnMove);
//         } else if (turn and (possibilities.at(0).num < returnMove.num)){
//             possibilities.clear();
//             possibilities.push_back(returnMove);
//         } else if(!turn and (possibilities.at(0).num > returnMove.num)){
//             possibilities.clear();
//             possibilities.push_back(returnMove);
//         }
//     }
//     int numPosMoves = possibilities.size();
//     return possibilities.at(rand() % numPosMoves);
// }

