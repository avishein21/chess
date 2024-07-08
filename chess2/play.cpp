#include "board.h"
#include "termfuncs.h"
#include "piecePage.h"
#include <iomanip>
#include "setBoard.h"
using namespace std;

void usage(){
    cerr << "Usage: ./Play [Dev]\n\n";
    cerr << "Dev: if argument is \"True\" the output will be optimized for";
    cerr << "debugging\n\n";
    return;
}

void optionsPage(string optionTag, string gameMode, string opponent, 
                int botColor){
    cout << "\n\n";
    cout << "Options (Select one of the five below)\n\n\n";
    cout << "Quit\t\t\t-\tExit the Program\n\n\n";
    cout << "Customize Colors\t-\tAdjust colors of board and pieces\n\n\n";
    cout << "Set Gamemode\t\t-\tCurrent Gamemode: " << gameMode << "\n\n\n";
    cout << "Choose Player\t\t-\tCurrent Opponent: " << opponent << endl;
    if(botColor){
        cout << "\t\t\t\tYou play as: ";
        if(botColor == 1){
            cout << "White";
        } else if(botColor == 2){
            cout << "Black";
        } else {
            cout << "Random";
        }
    }
    cout << "\n\n\nPlay\t\t\t-\tStart game\n";
    cout << "\t\t\t\t(To play, enter moves such as \"E2 E4\" to move\n";
    cout << "\t\t\t\tpawn from E2 to E4)\n\n\n\n";
    cout << optionTag;
}

void gameModeText(string request){
    cout << "\n\n\nOptions\n\n\n\n";
    cout << "Classic \t-\tNo variations\n\n\n\n";
    cout << "Blindfold\t-\tNormal chess, but the pieces are ";
    cout << "invisible\n\t\t\tThe previous move will be relayed above the ";
    cout << "board\n\n\n\n";
    cout << "Custom Position\t-\tSet up the board as you like\n\n\n\n";
    cout << request;
}

string setGamemode(){
    screen_clear();
    string line;
    gameModeText("Choose a gamemode: ");
    while(getline(cin, line)){
        if(line == "Classic"){
            return "Classic";
        } else if (line == "Blindfold"){
            return "Blindfold";
        } else if (line == "Custom Position"){
            return "Custom Position";
        }
        screen_clear();
        gameModeText("Invalid command, choose a gamemode above: ");
    }
    //Should never happen
    return "Classic";
}

void botOptions(string outLine){
    cout << "\n\nOptions\n\n";
    cout << "\n\nSingle Player\t-\tPlay moves for both white and black\n\n";
    cout << "\nRandall\t\t-\tRandall plays unpredictable moves, and is just ";
    cout << "learning\n\t\t\tto play the game.\n\n";
    cout << "\nTammy\t\t-\tTammy is ultra agressive, but doesn't think too";
    cout << " far ahead.\n\n\n";
    cout << "\nReggie\t\t-\tReggie plays defensively, but will snap\n\t\t\tup";
    cout << " a free piece if you let him.\n\n\n";
    cout << "\nParker\t\t-\tParker loves attacking.\n\n\n";
    cout << "\nFrancis\t\t-\tFrancis has been studying his tactics, and ";
    cout << "always\n\t\t\tenjoys a puzzle.\n\n\n";
    cout << "\nGerald\t\t-\tGerald has been playing chess for decades, so ";
    cout << "he'll take\n\t\t\this time to find the best move.\n\n\n";
    cout << outLine;
    return;
}

string botNameHelper(string Name, int *botColor, string line){
    if (line == Name){
        cout << "Type \"1\" to play as white, \"2\" to play as black,";
        cout << " \"3\" to play as random\nEnter choice here: ";
        while(getline(cin, line)){
            if (line == "1"){
                *botColor = 1;
                return Name;
            } else if (line == "2"){
                *botColor = 2;
                return Name;
            } else if (line == "3"){
                *botColor = 3;
                return Name;
            } else {
                *botColor = 0;
                return "";
            }
        }
    }
    return "";
}

string setBot(int *botColor){
    string line, tryName;
    screen_clear();
    botOptions("Choose a player: ");
    while(getline(cin, line)){
        if(line == "Single Player"){
            *botColor = 0;
            break;
        }
        tryName = botNameHelper("Randall", botColor, line);
        if(tryName != ""){
            return tryName;
        };
        tryName = botNameHelper("Tammy", botColor, line);
        if(tryName != ""){
            return tryName;
        };
        tryName = botNameHelper("Reggie", botColor, line);
        if(tryName != ""){
            return tryName;
        };
        tryName = botNameHelper("Francis", botColor, line);
        if(tryName != ""){
            return tryName;
        };
        tryName = botNameHelper("Parker", botColor, line);
        if(tryName != ""){
            return tryName;
        };
        tryName = botNameHelper("Gerald", botColor, line);
        if(tryName != ""){
            return tryName;
        };
        screen_clear();
        botOptions("Invalid choice. Choose a player from the options above: ");
    }
    return line;
}

int main(int argc, char *argv[]){
    string colors[4] = {"\033[1;30m", "\033[0m", "\033[1;100m", "\033[47m"};
    string line, gameMode = "Classic", opponent = "Single Player";
    int botColor = 0;
    if (argc == 2){
        if(!strcmp(argv[1], "True")){
            board theGame;
            theGame.play(colors, opponent, gameMode, true, 0);
        } else {
            usage();
        }
    } else if(argc == 1){
        screen_clear();
        optionsPage("Enter a command: ", gameMode, opponent, botColor);
        piecePage setColors;
        while(getline(cin, line)){
            if(line == "Play"){
                board theGame;
                theGame.play(colors, opponent, gameMode, false, botColor);
                screen_clear();
                optionsPage("Enter a command: ", gameMode, opponent, botColor);
            } else if(line == "Choose Player"){
                opponent = setBot(&botColor);
                screen_clear();
                optionsPage("Opponent set, enter a new command: ", gameMode, 
                            opponent, botColor);
            } else if(line == "Set Gamemode"){
                gameMode = setGamemode();
                screen_clear();
                optionsPage("Gamemode set, enter a new command: ", gameMode, 
                            opponent, botColor);
            } else if(line == "Customize Colors"){
                setColors.printPage(colors);
                optionsPage("Enter a command: ", gameMode, opponent, botColor);
            } else if(line == "Quit"){
                return 0;
            } else {
                screen_clear();
                optionsPage("Illegal command, please enter one from the list: ",
                            gameMode, opponent, botColor);
            }
        }
    } else {
        usage();
    }
    return 0;
}
