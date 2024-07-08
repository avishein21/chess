#include "acutest.h"
#include "fen.h"

void test_equal(){
    // TEST_CHECK_(4 == 4, "added %d and %d to %d", 2, 2, 4);
    TEST_CHECK_(4 == 4, "4 == 4");
}

void makeFenFront(){
    piece board[8][8];
    for (int i = 0; i < 64; i++){
        piece space;
        space.name = '.';
        space.player = 2;
        board [i / 8][i % 8] = space;
    }
    bool castle[4] = {true, false, true, true};
    fen temp(board, true, 30, 80, "A4", castle, false);
    // temp.makeFenStrFront();
    // fen temp1();
    TEST_CHECK_(1 == 1, "Linking");
    // TEST_CHECK_(temp.retHalfFen() == "8/8/8/8/8/8/8/8", "Print fen front");
}

// void fullString(){
//     piece board[8][8];
//     for (int i = 0; i < 64; i++){
//         piece space;
//         space.name = '.';
//         space.player = 2;
//         board [i / 8][i % 8] = space;
//     }
//     bool castle[4] = {true, false, true, true};
//     fen temp(board, true, 30, 80, "A4", castle, false);
//     temp.makeFenStrFront();
//     TEST_CHECK_(temp.makeFenString() == "8/8/8/8/8/8/8/8 w Kkq A4 15 41", "Print fen total");
// }

TEST_LIST = { 
    {"test1", test_equal},
    {"fen pt1", makeFenFront},
    // {"fen full", fullString},
    {0} 
};
