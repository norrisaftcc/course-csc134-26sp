/*
CSC 134
M5Lab1.cpp - Main Program
norrisa
11/5/25
*/

#include <iostream>
#include <string>
#include "m5lab1_gamejam.h" 
using namespace std;

// Utility Function Prototypes
int getPlayerChoice(int maxChoice);
void showChoices(string choice1, string choice2, string choice3);

int main() {
    cout << "--- 24-HOUR GAME JAM SIMULATOR ---" << endl;
    
    // Kick off the story defined in the header
    jam_start();

    cout << "\nThanks for playing the Game Jam simulator!" << endl;
    return 0;
}

// Utility Function Definitions
int getPlayerChoice(int maxChoice) {
    int choice;
    while (true) {
        cout << "Your choice (1-" << maxChoice << "): ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }
        if (choice >= 1 && choice <= maxChoice) {
            return choice;
        }
        cout << "Choice out of range." << endl;
    }
}

void showChoices(string choice1, string choice2, string choice3) {
    cout << "\n--------------------------" << endl;
    cout << "1. " << choice1 << endl;
    if (choice2 != "") cout << "2. " << choice2 << endl;
    if (choice3 != "") cout << "3. " << choice3 << endl;
    cout << "--------------------------" << endl;
}