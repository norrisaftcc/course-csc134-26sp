// CSC 134
// M3T2 - Craps!
// norrisa
// 2/16/26
// Start the game of craps.
#include <iostream>
using namespace std;

// Function declarations
// (Tell the program what functions will be!)
int roll();

// main() goes here
int main() {
    int number = roll();
    cout << "You rolled a " << number << endl;
    return 0;
}

// Function definitions
// (Actually write the ENTIRE function!)
int roll() {
    return 1; // these dice are loaded!
}