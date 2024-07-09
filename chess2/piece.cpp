#include <iostream>
#include <string>
#include "piece.h"
#include <vector>
using namespace std;


piece::piece() {
    //Bad default vals
    player = 4;
    name = 'E'; 
}

bool piece::move(int f1, int f2, int t1, int t2, piece * board[][8], 
                    string p, bool castle[]){
    (void) f1;
    (void) f2;
    (void) t1;
    (void) t2;
    (void) board;
    (void) p;
    (void) castle;
    return false;
}

bool piece::canCheck(int f1, int f2, piece * board[][8]){
    (void) f1;
    (void) f2;
    (void) board;
    return false;
}

vector <string> piece::canMove(int i, int j, bool turn, piece * board[][8]){
    (void) i;
    (void) j;
    (void) turn;
    (void) board;
    vector <string> noMove;
    return noMove;
}

void piece::makeSpace(){
    player = 2;
    name = '.'; 
}

void piece::undoSpace(){
    //empty
}

piece::~piece(){
    //empty
}

Space::Space(){
    player = 2;
    name = '.'; 
}

bool Space::move(int f1, int f2, int t1, int t2, piece * board[][8],
                  string p, bool castle[]){
    (void) f1;
    (void) f2;
    (void) t1;
    (void) t2;
    (void) board;
    (void) p;
    (void) castle;
    return false;
}

bool Space::canCheck(int f1, int f2, piece * board[][8]){
    (void) f1;
    (void) f2;
    (void) board;
    return false;
}

vector <string> Space::canMove(int i, int j, bool turn, piece * board[][8]){
    (void) i;
    (void) j;
    (void) turn;
    (void) board;
    vector <string> noMove;
    return noMove;
}

void Space::undoSpace(){
    //empty
}
