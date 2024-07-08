#include "piecePage.h"
#include "termfuncs.h"
#include <iostream>
using namespace std;
const string pieceArr[9] = {"\033[0m", "\033[0;30m", "\033[0;31m", "\033[0;32m",
                            "\033[0;33m","\033[0;34m","\033[0;35m","\033[0;36m",
                            "\033[0;37m"};

const string squareArr[9] = {"\033[47m", "\033[1;100m", "\033[1;101m", 
                            "\033[1;102m", "\033[1;103m", "\033[1;104m", 
                            "\033[1;105m","\033[1;106m", "\033[1;107m"};

void piecePage::printPieces(){
    cout << "\t";
    for(int i = 0; i < 9; i++){
        cout << pieceArr[i] << " ♟  ";
    }
    cout << "\033[0m\n\t\t\t\t";
    for(int i = 0; i < 9; i++){
        cout << " " << i << "  ";
    }
    cout << endl;
    return;
}

void piecePage::printSquares(){
    cout << "\t";
    for(int i = 0; i < 9; i++){
        cout << squareArr[i] << " ♟ \033[0m ";
    }
    cout << "\033[0m\n\t\t\t\t";
    for(int i = 0; i < 9; i++){
        cout << " " << i << "  ";
    }
    cout << endl;
    return;
}

void piecePage::intro(string colors[], string newMessage){
    cout << "\n\nType \"Quit\" to return home\n\n\n\n";
    cout << "Choose a color for your piece or board\n\n";
    cout << "(Example: 1 3 for \033[0;32m♟\033[0m)\n\n\n";
    cout << "1 (White Pieces) \t-";
    printPieces();
    cout << "2 (Black Pieces) \t-";
    printPieces();
    cout << "3 (White Squares) \t-";
    printSquares();
    cout << "4 (Black Squares) \t-";
    printSquares();
    cout << "5 (Reset)\n\n";
    cout << "Current Board \n";
    printBoard(colors);
    cout << newMessage;
    return;
}

void piecePage::printRow(bool start, string piece, string colors[]){
    string pieceColor = colors[1];
    if(start){
        pieceColor = colors[0];
    }
    for (int i = 0; i < 4; i++){
        if((start + i) % 2){
            cout << pieceColor;
            cout << colors[3];
        } else {
            cout << pieceColor;
            cout << colors[2];
        }
        cout << piece;
    }
    cout << "\033[0m\n";
}

void piecePage::printBoard(string colors[]){
    printRow(true, " ♟ ", colors);
    printRow(false, "   ", colors);
    printRow(true, "   ", colors);
    printRow(false, " ♟ ", colors);
}

void piecePage::setPieceColor(string colors[], bool pos, char newColor){
    int colorPos = newColor - '0';
    colors[pos] = pieceArr[colorPos];
    return;
}

void piecePage::setSquareColor(string colors[], bool pos, char newColor){
    int colorPos = newColor - '0';
    colors[pos + 2] = squareArr[colorPos];
    return;
}

bool piecePage::checkLine(char type, string line){
    bool temp1 = ((line[0] == type) and (line[2] >= '0'));
    bool temp2 = ((line[2] <= '8') and (line[1] == ' '));
    return (temp1 and temp2 and (line.length() == 3));
}

void piecePage::printPage(string colorArr[]){
    screen_clear();
    string line;
    intro(colorArr, "\nEnter here: ");
    string message;
    while(getline(cin, line)){
        if(line == "Quit"){
            screen_clear();
            return;
        } else if (checkLine('1', line)){
            message = "\nWhite pieces changed, enter a new command: ";
            setPieceColor(colorArr, true, line[2]);
        } else if (checkLine('2', line)){
            message = "\nBlack pieces changed, enter a new command: ";
            setPieceColor(colorArr, false, line[2]);
        } else if (checkLine('3', line)){
            message = "\nWhite squares changed, enter a new command: ";
            setSquareColor(colorArr, true, line[2]);
        } else if (checkLine('4', line)){
            message = "\nBlack squares changed, enter a new command: ";
            setSquareColor(colorArr, false, line[2]);
        } else if ((line[0] == '5') and (line.length() == 1)) {
            message = "\nBoard reset, enter a new command: ";
            colorArr[0] = "\033[1;30m";
            colorArr[1] = "\033[0m";
            colorArr[2] = "\033[1;100m";
            colorArr[3] = "\033[47m";
        } else {
            message = "\nIllegal command, try again: ";
        }
        screen_clear();
        intro(colorArr, message);
    }
    return;
}
