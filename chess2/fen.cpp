#include "fen.h"
#include "knight.h"
#include "rook.h"
#include "bish.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"
#include <iostream>
#include <stdio.h>
#include "setBoard.h"
using namespace std;


//get all info to make fen
fen::fen(piece * givenBoard[][8], bool playTurn, int moves, int allMoves, 
            string pessSquare, bool castle[])
{
    for (int i = 0; i < 64; i++){
        board[i / 8][i % 8] = givenBoard[i / 8][i % 8];
    }
    turn = playTurn;
    moves50 = moves;
    moveNum = allMoves / 2 + 1;
    pessant = pessSquare;
    wCastL = castle[0];
    wCastR = castle[1];
    bCastL = castle[2];
    bCastR = castle[3];
}

//set up with full fen string
fen::fen(string fenStr){
    int curr = 0; //current letter
    int i = 0; //squares filled
    char currLetter;
    while (i < 64){
        currLetter = fenStr[curr];
        if (isdigit(currLetter)){
            for (int j = 0; j < currLetter - 48; j++){
                board[i/8][i%8] = new Space();
                i++;
            }
        //black 
        } else if (currLetter > 97){
            board[i/8][i%8]= setBoard::makePiece(currLetter - (97 - 65), false);
            i++;
        // white
        } else if (currLetter > 65){
            board[i/8][i%8]= setBoard::makePiece(currLetter, true);
            i++;
        }
        //else slash
        curr++;
    }
}

//normal board
fen::fen(){
    board[0][0] = new rook(false);
    board[0][1] = new knight(false);
    board[0][2] = new bish(false);
    board[0][3] = new queen(false);
    board[0][4] = new king(false);
    board[0][5] = new bish(false);
    board[0][6] = new knight(false);
    board[0][7] = new rook(false);
    for (int i = 0; i < 8; i++){
        board[1][i] = new pawn(false);
    }
    //Middle Spaces
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++){
            board[i][j] = new Space();
        }
    }
    //White Side
    for (int i = 0; i < 8; i++){
        board[6][i] = new pawn(true);
    }
    board[7][0] = new rook(true);
    board[7][1] = new knight(true);
    board[7][2] = new bish(true);
    board[7][3] = new queen(true);
    board[7][4] = new king(true);
    board[7][5] = new bish(true);
    board[7][6] = new knight(true);
    board[7][7] = new rook(true);
    halfFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
}

//returns board part of fen
string fen::retHalfFen(){
    if (halfFen != ""){
        return halfFen;
    }
    string retString = halfFen;
    bool prevPiece = true;
    piece * temp;
    for (int i = 0; i < 64; i++){
        if (not (i % 8) and (i != 0)){
            retString += "/";
            prevPiece = true;
        }
        temp = board[i/8][i%8];
        if (temp->player == 2){
            if (not prevPiece){
                retString[retString.length() - 1]++;
            } else {
                retString += "1";
            }
            prevPiece = false;
        } else {
            if (temp->player == 0){
                retString += temp->name + (97 - 65);
            } else {
                retString += temp->name;
            }
            prevPiece = true;
        }
    }
    halfFen = retString;
    return halfFen;
}

//make full string
string fen::makeFenString(){
    if (fullFen != ""){
        return fullFen;
    }
    // change to halfFen after implementing 3 rep
    string retString = retHalfFen();
    if (turn){
        retString += " w ";
    } else {
        retString += " b ";
    }
    // //Board, color to move, Castling, pessant square, 50 moves, total moves
    if (not (wCastL or wCastR or bCastL or bCastR)){
        retString += "-";
    } else {
        if(wCastL){
            retString += 'K';
        }
        if(wCastR){
            retString += 'Q';
        }
        if(bCastL){
            retString += 'k';
        }
        if(bCastR){
            retString += 'q';
        }
    }
    if(pessant == ""){
        retString += " - ";
    } else {
        string retPes = pessant;
        retPes[0] += (97 - 65);
        retString += " " + retPes + " ";
    }
    retString += to_string(moves50) + " " + to_string(moveNum); 
    return retString; 
}

//takes board and overwrites it with board saved in FEN
void fen::retBoard(piece * givenBoard[][8]){
    for (int i = 0; i < 64; i++){
        givenBoard[i / 8][i % 8] = board[i / 8][i % 8];
    }
}

//sets fen board to given board
void fen::updateBoard(piece * givenBoard[][8]){
    for (int i = 0; i < 64; i++){
        board[i / 8][i % 8] = givenBoard[i / 8][i % 8];
    }
    halfFen = "";
    fullFen = "";
}

//returns whos turn it is
bool fen::retTurn(){
    return turn;
}

//returns move count to 50 move rule
int fen::retMove50(){
    return moves50;
}

//returns what move it is total
int fen::retMoveNum(){
    return moveNum;
}

//returns passant square
string fen::retPessant(){
    return pessant;
}

//returns castle values as array
bool * fen::retCastle(){
    static bool castle[4] = {wCastL, wCastR ,bCastL, bCastR}; 
    return castle;
}

//ALL FUNCS BELOW RETURN TRUE IF POSSIBLE, FALSE IF NOT

//sets turn
bool fen::setTurn(string tChar){
    if (tChar == "w"){
        turn = true;
    } else if (tChar == "b"){
        turn = false;
    } else {
        return false;
    }
    return true;
}

//updates 4 castle values
bool fen::updateCastle(string test){
    string fullCast = "KQkq";
    int fullCount = 0;
    int testCount = 0;
    int fLen = fullCast.length();
    int tLen = test.length();
    wCastL = false;
    bCastL = false;
    wCastR = false;
    bCastR = false;
    if (test == "-"){
        return true;
    } else {
        while((fullCount < fLen) and (testCount < tLen)){ 
            if (fullCast[fullCount] == test[testCount]){
                if (fullCast[fullCount] == 'K'){
                    wCastL = true;
                } else if (fullCast[fullCount] == 'Q'){
                    wCastR = true;
                } else if (fullCast[fullCount] == 'k'){
                    bCastL = true;
                } else {
                    bCastR = true;
                }
                testCount++;
            }
            fullCount++;
        }
        if (testCount != tLen){
            return false;
        }
        return true;
    }
}

//updates en pessant square
bool fen::updatePessant(string Square){
    if (Square == "-"){
        pessant = "";
        return true;
    }
    if (Square.length() != 2){
        return false;
    } else if (Square[0] < 'a' or Square[0] > 'h'){
        return false;
    } else if (Square[1] < '1' or Square[1] > '8'){
        return false;
    } else {
        Square[0] -= (97 - 65);
        pessant = Square;
        return true;
    }
}

//updates moves to 50
bool fen::update50(string num){
    if(!isNum(num)){
        return false;
    } 
    int valid = stoi(num);
    if (valid >= 100 or valid < 0){
        return false;
    }
    moves50 = valid;
    return true;
}

//updates move number
bool fen::updateAllMoves(string num){
    if(!isNum(num)){
        return false;
    } 
    int valid = stoi(num);
    if (valid < 0){
        return false;
    }
    moveNum = valid;
    return true;
}

//helper to check if a string is a number
bool fen::isNum(string num){
    int len = num.length();
    for (int i = 0; i < len; i++) {
        if(!isdigit(num[i])){
            return false;
        }
    }
    return true;
}

fen::~fen(){
    //
}
