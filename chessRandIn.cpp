#include <iostream>
using namespace std;
#include<cstdlib>
#include <vector>
// clang++ -g3 -Wall -Wextra -Wpedantic -Wshadow chessRandIn.cpp -o makeInputs

int main()
{
    srand (time(NULL));
    // int commands;
    // cin >> commands;
    // cout << "Play\n";
    for (long int i = 0; i < 1000000; i++)
    {
        char letter1 = rand() % 8 + 65;
        int num1 = rand() % 8 + 1;
        char letter2 = rand() % 8 + 65;
        int num2 = rand() % 8 + 1;
        cout << letter1 << num1 << " " << letter2 << num2 << endl;
    }
    cout << "Quit" << endl;
    return 0;
}
