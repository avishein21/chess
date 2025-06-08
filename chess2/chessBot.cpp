#include "checkPiece.h"
#include <vector>
#include "chessBot.h"
#include <cstdlib>
#include <thread>
#include "setBoard.h"
// #include <chrono>


const int CHECKMATE = 100000;
const int STALEMATE = -10000;

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds


chessBot::chessBot(string opp){
    if (opp == "Randall"){ depth = 0; } 
    else if (opp == "Tammy"){  depth = 1; } 
    else if (opp == "Reggie"){  depth = 2; } 
    else if (opp == "Parker"){  depth = 3; } 
    else if (opp == "Francis"){  depth = 4; } 
    else if (opp == "Gerald"){  depth = 5; } 
    else {depth = 1; }
}

string chessBot::botMove(piece *board[][8], bool turn){
    system_clock::time_point t = system_clock::now();
    string move;
    if (depth == 0) { move = randall(board, turn); } 
    else { move = engine(board, turn, depth).move; }
    sleep_until(t + seconds(1));
    return move;
}

// Gets a random move from the all moves vector
string chessBot::randall(piece *board[][8], bool turn){
    srand(time(0));
    vector <string> allMovables = allMoves(board, turn);
    int move = rand() % allMovables.size();
    return allMovables.at(move);
}

// Gets a move and its associated value for given depth
numMove chessBot::engine(piece *board[][8], bool turn, int deep){
    // get all moves
    vector <string> allMovables = allMoves(board, turn);
    vector <numMove> moveRatings;
    // -1 for black, 1 for white
    int mult = turn * 2 - 1;

    // All future moves and their values
    vector<string>::iterator it;
    for (it = allMovables.begin(); it != allMovables.end(); it++) {
        // make board copy and make move on copy
        piece *copyBoard[8][8];
        setBoard::copyBoard(board, copyBoard);
        checkPiece copiedMove(copyBoard, -1);
        // make move on board
        copiedMove.makeMove(*it, copyBoard, false, thm, "");
        checkPiece check_for_mate(copyBoard, -1);

        // if checkmate or stalemate, add new rating for move
        if (!check_for_mate.canMove(!turn)){
            if (check_for_mate.canCheck(!turn)){
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
                numMove oppMove = engine(copyBoard, !turn, deep - 1);
                oppMove.num *= -1;
                oppMove.move = *it;
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

// returns all possible moves
vector <string> chessBot::allMoves(piece *board[][8], bool turn){
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
