/*
CSC 134
M5Lab1.h - The 24-Hour Game Jam
*/

#ifndef M5LAB1_H
#define M5LAB1_H

#include <iostream>
#include <string>
using namespace std;

// Prototypes for the utility functions (defined in .cpp)
extern void showChoices(string, string, string);
extern int getPlayerChoice(int);

// Story Branch Prototypes
void jam_start();
void path_caffeine_chaos();
void path_ai_assistant();
void path_slow_and_steady();
void ending_good();
void ending_ok();
void ending_bad();

// --- Story Function Definitions ---

void jam_start() {
    int choice;
    cout << R"(
It's 10:00 AM. The Game Jam has just begun. 
Theme: "Recursion." You have 24 hours to ship a game.
How do you start your morning?
    )" << endl;

    showChoices("Three shots of espresso.", 
                "Open a clean IDE and start coding solo.", 
                "Immediately ask AI to generate the engine.");
    
    choice = getPlayerChoice(3);

    if (choice == 1) {
        path_caffeine_chaos();
    } else if (choice == 2) {
        path_slow_and_steady();
    } else {
        path_ai_assistant();
    }
}

void path_caffeine_chaos() {
    int choice;
    cout << "\n--- 8 HOURS IN: THE VIBRATION STAGE ---" << endl;
    cout << "You can see through time. Your code is fast, but your hands " << endl;
    cout << "are shaking so hard you keep typing 'viod' instead of 'void'." << endl;

    showChoices("Take a 20-minute power nap.", 
                "Push through with more energy drinks.", 
                "Pivot to a text-based game to save time.");
    
    choice = getPlayerChoice(3);

    if (choice == 1) {
        ending_ok(); // Nap saved you, but you lost time
    } else if (choice == 2) {
        ending_bad(); // Heart palpitations are not a game mechanic
    } else {
        ending_good(); // Smart pivot!
    }
}

void path_ai_assistant() {
    int choice;
    cout << "\n--- 16 HOURS IN: THE PROMPT STRUGGLE ---" << endl;
    cout << "The AI generated a beautiful engine, but you have no idea " << endl;
    cout << "how it works. A bug appeared in a language you don't speak." << endl;

    showChoices("Spend 4 hours debugging the AI's mess.", 
                "Ask the AI to fix the bug (Risky).", 
                "Delete it all and start over.");
    
    choice = getPlayerChoice(3);

    if (choice == 1) {
        ending_ok();
    } else if (choice == 2) {
        ending_bad(); // The AI deleted your hard drive
    } else {
        path_slow_and_steady(); // Back to basics
    }
}

void path_slow_and_steady() {
    cout << "\n--- 22 HOURS IN: THE FINAL STRETCH ---" << endl;
    cout << "You're tired, but your code is clean. The game is simple " << endl;
    cout << "but it actually runs without crashing." << endl;
    ending_good();
}

// --- Endings ---

void ending_good() {
    cout << "\n[ ENDING: THE INDIE DARLING ]" << endl;
    cout << "Your game is a hit! It's bug-free and fun. You win the jam!" << endl;
}

void ending_ok() {
    cout << "\n[ ENDING: THE 'IT WORKS ON MY MACHINE' ]" << endl;
    cout << "You submitted 5 minutes late. It's buggy, but people like the art." << endl;
}

void ending_bad() {
    cout << "\n[ ENDING: THE BLUE SCREEN OF DEATH ]" << endl;
    cout << "You fell asleep on your keyboard at 3 AM. Your project is " << endl;
    cout << "just 400 lines of the letter 's'. Better luck next year." << endl;
}

#endif