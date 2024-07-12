#include "setBoard.h"
#include "termfuncs.h"
#include "pieces/knight.h"
#include "pieces/rook.h"
#include "pieces/bish.h"
#include "pieces/queen.h"
#include "pieces/king.h"
#include "pieces/pawn.h"
#include "pieces/piece.h"
#include "fen.h"
#include <iostream>
#include <sstream>
using namespace std;

//Returns normal board
void setBoard::normalBoard(piece * board[][8]){
    fen norm;
    norm.retBoard(board);
}

//Prints fully formatted board
void setBoard::printBoard(piece * board[][8], string theme[], string gameMode, 
                        bool gameOver){
    cout << "\033[1;4;34m | A  B  C  D  E  F  G  H \033[0m";
    int material = boardPoints(board);
    if(not gameOver){
        if(material == 0){
            cout << "\tMaterial: Even";
        } else if (material > 0){
            cout << "\tMaterial: White +" << material;
        } else {
            cout << "\tMaterial: Black +" << material * (-1);
        }
    }
    cout << endl;
    for (int j = 0; j < 8; j++) { 
        cout << "\033[1;34m" << 8 - j <<  "|\033[0m";
        for (int i = 0; i < 8; i ++){
            if (board[j][i]->player == 0) {
                //black piece color
                cout << theme[0];
            } else {
                //white piece color
                cout << theme[1];
            }
            //backgroud
            if ((i + j) % 2){
                cout << theme[2];
            } else {
                cout << theme[3];
            }
            prettyPiece(board[j][i]->name, gameMode);
            cout << "\033[0m";
            if (i == 7){
                cout << endl;
            }
        }
    }
    cout << "\033[0m ";
    cout << endl;
}

//Text to tells user how to set up custom board
void setBoard::setOptions(string returnCom, piece * useBoard[][8], 
                            string colors[], fen currFen){
    screen_clear();
    cout << "\n\nType \"Play\" to continue to game\n\n";
    cout << "Type \"Clear\" clear board\n\n";
    cout << "Type \"Reset\" reset board to classic\n\n";
    cout << "Type \"Delete\" followed by a square on the board to delete a ";
    cout << "piece\n(For example, \"Delete E2\" will delete the pawn on E2)\n\n";
    cout << "Type \"Add\" followed by a piece color (White/Black), a piece ";
    cout << "type\n(Pawn/Rook/Knight/Bishop/Queen/King) and a square on the ";
    cout << "board to add a piece\n(For example, \"Add Black Bishop E5\" will ";
    cout << "place a black bishop on E5)\n\nOR\n\n";
    cout << "Enter a position using a chess.com FEN. The current board FEN";
    cout << " is:\n";
    cout << currFen.makeFenString() << "\n\n";
    cout << "Turn: ";
    if(currFen.retTurn()){
        cout << "White";
    } else {
        cout << "Black";
    }
    cout << endl << endl;
    printBoard(useBoard, colors, "Classic", false);
    cout << returnCom;
}

//Gets user input to update board
fen setBoard::customBoard(piece * useBoard[][8], string colors[]){
    string line = "";
    fen retfen;
    retfen.retBoard(useBoard);
    setOptions("Enter a command: ", useBoard, colors, retfen);
    string returnCom;
    while(line != "Play"){
        getline(cin, line);
        if(line == "Clear"){
            clearBoard(useBoard);
            returnCom = "Board cleared, enter a new command: ";
            retfen.updateBoard(useBoard);
        } else if (line == "Reset"){
            setBoard::cleanBoard(useBoard);
            normalBoard(useBoard);
            retfen.updateBoard(useBoard);
            returnCom = "Board reset, enter a new command: ";
        } else if ((line.substr(0, 6) == "Delete") and (line.length() == 9)){
            returnCom = deletePiece(line, useBoard);
            retfen.updateBoard(useBoard);
        } else if (line.substr(0, 3) == "Add"){
            returnCom = addPiece(line, useBoard);
            retfen.updateBoard(useBoard);
        } else if (validFen(line, retfen)){
            setFullBoard(line, useBoard);
            returnCom = "Board Set: ";
        } else {            
            returnCom =  "Invalid command, please enter ";
            returnCom += "one as specified above: ";
        }
        setOptions(returnCom, useBoard, colors, retfen);
    }
    
    return retfen;
}

//Checks if line in FEN board has 8 peices
bool setBoard::lineVal(string testString){
    char temp;
    int sum = 0;
    int len = testString.length();
    for (int i = 0; i < len; i++){
        temp = testString[i];
        if(temp == 'r' or temp == 'n' or temp == 'b' or temp == 'k' or 
        temp == 'q' or temp == 'p' or temp == 'R' or temp == 'N' or temp == 'B' 
        or temp == 'K' or temp == 'Q' or temp == 'P'){
            sum++;
        } else if (isdigit(temp)){
            sum += (temp - 48);
        } else {
            sum += 10;
        }
    }
    if (sum == 8){
        return true;
    }
    return false;
}


//Checks if FEN is valid, and updates position if possible
bool setBoard::validFen(string testString, fen &makeFen){
    stringstream s(testString);
    string word; 
    //Board string
    s >> word;
    if(not validBoard(word)){ return false; }
    fen tempF(word);
    //Turn string
    s >> word;
    if(not tempF.setTurn(word)){ return delFen(tempF); }
    //Castle string
    s >> word;
    if(not tempF.updateCastle(word)){ return delFen(tempF); }

    //Pasant string
    s >> word;
    if(not tempF.updatePessant(word)){ return delFen(tempF); }
    
    //50Moves string
    s >> word;
    if(not tempF.update50(word)){ return delFen(tempF); }
    
    //All moves string
    s >> word;
    if(not tempF.updateAllMoves(word)){ return delFen(tempF); }
    
    //If all else passed and string ended, return true and new FEN
    s >> word;
    if (not s){
        delFen(makeFen);
        makeFen = tempF;
        return not delFen(tempF);
    }
    return false;
}

//Deletes current fen board
bool setBoard::delFen(fen deleting){
    piece * fenBoard[8][8];
    deleting.retBoard(fenBoard);
    setBoard::cleanBoard(fenBoard);
    return false;
}

//Takes first string checks if the board is valid
bool setBoard::validBoard(string boardStr){
    int slashes = 0, start = 0, chars = 0, curr = 0;
    char testing = boardStr[0];
    while (slashes < 7){
        testing = boardStr[curr];
        chars++;
        if (testing == '/'){
            slashes++;
            if(not lineVal(boardStr.substr(start, chars - 1))){
                return false;
            };
            start += chars;
            chars = 0;
        }
        curr++;
    }
    if (not (slashes == 7)){
        return false;
    }
    //Check last row
    if(not lineVal(boardStr.substr(curr, boardStr.length() - 1))){
        return false;
    };
    return true;
}


//Takes a valid string and updates the board to match
void setBoard::setFullBoard(string boardString, piece * useBoard[][8]){
    int curr = 0; //current letter
    int i = 0; //squares filled
    char currLetter;
    while (i < 64){
        currLetter = boardString[curr];
        if (isdigit(currLetter)){
            for (int j = 0; j < currLetter - 48; j++){
                // delete useBoard[i/8][i%8];
                useBoard[i/8][i%8] = new Space();
                i++;
            }
        //black 
        } else if (currLetter > 97){
            // delete useBoard[i/8][i%8];
            useBoard[i/8][i%8] = setBoard::makePiece(currLetter - 32, false);
            i++;
        // white
        } else if (currLetter > 65){
            // delete useBoard[i/8][i%8];
            useBoard[i/8][i%8] = setBoard::makePiece(currLetter, true);
            i++;
        }
        //else slash
        curr++;
    }
}

//Adds a piece to a square if possible
string setBoard::addPiece(string line, piece * useBoard[][8]){
    int color;
    if(line.length() < 4){
        return "Enter entire \"Add\" command on one line, please try again: ";
    } else if (line[3] != ' '){
        return "No space after \"Add\", enter a new command: ";
    } else if (line.length() < 9){
        return "Piece color invalid, enter a new command: ";
    } else if (line.substr(4,5) == "Black"){
        color = 0;
    } else if (line.substr(4,5) == "White"){
        color = 1;
    } else {
        return "Piece color invalid, enter a new command: ";
    }
    if(line.length() < 10){
        return "Please include a piece and square, enter a new command: ";
    } else if (line[9] != ' '){
        return "No space after piece color, enter a new command: ";
    } else if (line.length() == 17){
        if (placePiece(line, useBoard, "Pawn", color) or 
        placePiece(line, useBoard, "Rook", color) or 
        placePiece(line, useBoard, "King", color)){
            return "Piece Placed, enter a new command: ";
        }
    } else if (line.length() == 18){
        if (placePiece(line, useBoard, "Queen", color)){
            return "Piece Placed, enter a new command: ";
        }
    } else if (line.length() == 19){
        if (placePiece(line, useBoard, "Knight", color)){
            return "Piece Placed, enter a new command: ";
        }
        if (placePiece(line, useBoard, "Bishop", color)){
            return "Piece Placed, enter a new command: ";
        }
    }
    return "Invalid piece or square, enter a new command: ";   
}

//Helper for add piece
bool setBoard::placePiece(string line, piece * useBoard[][8], string tryName, 
                            int color){
    int nameLength = tryName.length();
    string pieceName = line.substr(10, nameLength);
    if(pieceName != tryName){
        return false;
    } else if (line[10 + nameLength] != ' '){
        return false;
    } else {
        //Find the square and place the piece
        string square = line.substr(11 + nameLength,2);
        if((square[0] < 'A') or (square[0] > 'H') or 
        (square[1] < '1') or (square[1] > '8')){
            return false;
        } else {
            piece * placed;
            if (pieceName == "Knight"){
                placed = makePiece('N', color);
            } else {
                placed = makePiece(pieceName[0], color);
            }
            delete useBoard[7 - (square[1] - '1')][square[0] - 'A'];
            useBoard[7 - (square[1] - '1')][square[0] - 'A'] = placed;
            return true; 
        }
    }
}

piece * setBoard::makePiece(char let, bool color){
    switch (let){
    case 'R':
        return new rook(color);
    case 'N':
        return new knight(color);
    case 'B':
        return new bish(color);
    case 'K':
        return new king(color);
    case 'Q':
        return new queen(color);
    case 'P':
        return new pawn(color);
    default:
        return new Space();
    }
}

//Deletes all peices
void setBoard::clearBoard(piece * useBoard[][8]){
    for (int i = 0; i < 64; i++){
        delete useBoard[i%8][i/8]; 
        useBoard[i%8][i/8] = new Space(); 
    }  
}

//Deletes a piece from a square
string setBoard::deletePiece(string line, piece * useBoard[][8]){
    if((line[6] != ' ') or (line[7] < 'A') or (line[7] > 'H') or 
        (line[8] < '1') or (line[8] > '8')){
        return "Invalid command, please enter one as specified above: ";
    } else if (useBoard[7 - (line[8] - '1')][line[7] - 'A']->name == '.'){
        return "No piece on " + line.substr(7,2)+ ", enter a new command: ";
    } else {
        delete useBoard[7 - (line[8] - '1')][line[7] - 'A'];
        useBoard[7 - (line[8] - '1')][line[7] - 'A'] = new Space();
        string temp = "Piece deleted on " + line.substr(7,2);
        return temp + ", enter a new command: ";
    }
}

void setBoard::prettyPiece(char Name, string gameMode){
    if(gameMode == "Blindfold"){
        cout << "   ";
    } else if(Name == 'R'){
        cout << " ♜ ";
    } else if (Name == 'B'){
        cout << " ♝ ";
    } else if (Name == 'N'){
        cout << " ♞ ";
    } else if (Name == 'Q'){
        cout << " ♛ ";
    } else if (Name == 'K'){
        cout << " ♚ ";
    } else if (Name == 'P'){
        cout << " ♟ ";
    } else {
        cout << "   ";
    }
    cout << "\033[0m";
    return;
}

int setBoard::boardPoints(piece * board[][8]){
    int totalPts = 0;
    for (int j = 0; j < 64; j++){
        piece * temp = board[j / 8][j % 8];
        if(temp->player == 1){
            totalPts += piecePoints(temp->name);
        } else if (temp->player == 0){
            totalPts -= piecePoints(temp->name);
        }
    }
    return totalPts;
}

int setBoard::piecePoints(char pieceName){
    switch (pieceName){
        case 'R':
            return 5;
        case 'N':
            return 3;
        case 'B':
            return 3;
        case 'K':
            return 3;
        case 'Q':
            return 9;
        case 'P':
            return 1;
        default:
            return 0;
    }
}

string setBoard::pieceName(char pieceName){
    if(pieceName == 'K'){
        return "King";
    } else if (pieceName == 'Q'){
        return "Queen";
    } else if (pieceName == 'R'){
        return "Rook";
    } else if (pieceName == 'B'){
        return "Bishop";
    } else if (pieceName == 'P'){
        return "Pawn";
    } else {
        return "Knight";
    }
}

void setBoard::cleanBoard(piece * board[][8]){
    for (int i = 0; i < 64; i++){
        delete board[i % 8][i / 8];
    }
}
