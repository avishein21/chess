#include "checkPiece.h"
#include <vector>
#include "chessBot.h"
#include <cstdlib>
#include <thread>
#include "setBoard.h"
// #include "king.h"
// #include "knight.h"
// #include "rook.h"
// #include "bish.h"
// #include "pawn.h"

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds


chessBot::chessBot(bool t, string opp){
    if (opp == "Randall"){
        depth = 0;
    } else {
        depth = 2;
    }
    turn = t;
}

string chessBot::botMove(piece *board[][8]){
    if (depth == 0) { return randall(board); } 
    else { return ""; }
}


// Gets a random move from the all moves vector
string chessBot::randall(piece *board[][8]){
    // Sleep
    sleep_until(system_clock::now() + seconds(1));
    // Get a random move
    vector <string> allMovables = allMoves(board);
    int move = rand() % allMovables.size();
    return allMovables.at(move);
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
    }
    return allMovables;
}
// }

// int chessBot::updateBestMove(int moveLess, int moveMore, int i, bool turn,
//                             vector <string>& holdMove, vector <string> allMove){
//     if(moveLess == moveMore){
//         holdMove.push_back(allMove.at(i));
//         return moveLess;
//     }
//     //White sees if the new move is greater
//     if (turn){
//         if(moveLess < moveMore){
//             holdMove.clear();
//             holdMove.push_back(allMove.at(i));
//             return moveMore;
//         }
//         return moveLess;
//     } 
//     //Black sees if the new move is greater
//     if(moveLess < moveMore){
//         holdMove.clear();
//         holdMove.push_back(allMove.at(i));
//         return moveLess;
//     }
//     return moveMore;
// }

// int chessBot::bestOneMove(bool turn, piece board[][8], string *moveName,
//                             int startComp, int bestCase, int staleMate){
//     vector <string> allMovables = allMoves(turn, board);
//     int length = allMovables.size();
//     checkPiece testPiece(board, "");
//     int mostPts = startComp;
//     vector <string> holdMove;
//     for(int i = 0; i < length; i++){
//         //temp board removable? 
//         piece tempBoard[8][8];
//         for(int j = 0; j < 64; j++){
//             tempBoard[j%8][j/8] = board[j%8][j/8];
//         }
//         bool castle[] = {false, false, false, false};
//         string theme[] = {"bogus"};
//         testPiece.makeMove(allMovables.at(i), tempBoard, castle, false, 
//                             theme, "Classic");
//         //Checkmate or stalemate
//         if (!testPiece.canMove(!turn)){
//             if(testPiece.canCheck(!turn)){
//                 //Checkmate
//                 holdMove.clear();
//                 holdMove.push_back(allMovables.at(i));
//                 mostPts = bestCase;
//                 break;
//             } else {
//                 //Stalemate
//                 int testPts = staleMate;
//                 mostPts = updateBestMove(mostPts, testPts, i, turn, holdMove,
//                         allMovables);
//             }
//         } else {
//             int testPts = setBoard::boardPoints(tempBoard);
//             if(turn){
//                 mostPts = updateBestMove(mostPts, testPts, i, turn, holdMove,
//                                         allMovables);
//             } else {
//                 mostPts = updateBestMove(testPts, mostPts, i, turn, holdMove,
//                         allMovables);
//             }
//         }
//     }
//     srand (time(NULL));
//     if (holdMove.size() != 0){
//         int move;
//         move = rand() % holdMove.size();
//         *moveName = holdMove.at(move);
//         return mostPts;
//     }
//     //Should not be reached (stalemate would have already been called)
//     return startComp;
// }

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


// string chessBot::tammy(bool turn, piece board[][8]){
//     sleep_until(system_clock::now() + seconds(1));
//     string bestMove;
//     if(turn){
//         //White best move in 1
//         bestOneMove(turn, board, &bestMove, INT_MIN, INT_MAX, INT16_MIN);
//         return bestMove;
//     } else {
//         //Black best move in 1
//         bestOneMove(turn, board, &bestMove, INT_MAX, INT_MIN, INT16_MAX);
//         return bestMove;
//     }
// }

// string chessBot::reggie(bool turn, piece board[][8]){
//     sleep_until(system_clock::now() + seconds(1));
//     return engine(turn, board, 1).move;
// }

// string chessBot::parker(bool turn, piece board[][8]){
//     return engine(turn, board, 2).move;
// }

// string chessBot::francis(bool turn, piece board[][8]){
//     return engine(turn, board, 3).move;
// }

// string chessBot::gerald(bool turn, piece board[][8]){
//     return engine(turn, board, 4).move;
// }
