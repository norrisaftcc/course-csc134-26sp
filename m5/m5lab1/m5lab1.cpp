/*
CSC 134
M5Lab1.cpp - Main Program
norrisa and Gemini
11/5/25
*/

#include <iostream>
#include "m5lab1.h" // Include your story file here!
using namespace std;

// Utility Function Prototypes
int getPlayerChoice(int maxChoice);
void showChoices(string choice1, string choice2, string choice3);

int main() {
    cout << "--- Welcome to the Spooky House Adventure ---" << endl;
    
    // Start the story
    game_start();

    cout << "\nThanks for playing!" << endl;
    return 0;
}

// Utility Function Definitions
int getPlayerChoice(int maxChoice) {
    int choice;
    while (true) {
        cout << "Your choice: ";
        if (!(cin >> choice)) { // Check for non-numeric input
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Please enter a number." << endl;
            continue;
        }
        if (choice >= 1 && choice <= maxChoice) {
            return choice;
        }
        cout << "Please choose between 1 and " << maxChoice << ".\n";
    }
}

void showChoices(string choice1, string choice2, string choice3) {
    cout << "---- MAKE YOUR CHOICE ----" << endl;
    int num = 1;
    cout << num << ". " << choice1 << endl;
    num++;

    if (choice2 != "") {
        cout << num << ". " << choice2 << endl;
        num++;
    }

    if (choice3 != "") {
        cout << num << ". " << choice3 << endl;
        num++;
    }
}