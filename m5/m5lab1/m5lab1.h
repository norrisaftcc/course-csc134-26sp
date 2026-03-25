/*
CSC 134
M5Lab1.h - Story Choices
norrisa and Gemini
*/

#ifndef M5LAB1_H
#define M5LAB1_H

#include <iostream>
#include <string>
using namespace std;

// Function Prototypes for story branches
void game_start();
void front_door_path(); // Branch 1
void garden_path();     // Branch 2
void go_home();        // Branch 3 (Ending)

// --- Story Function Definitions ---

void game_start() {
    int choice;
    const int MAX = 3;

    cout << R"(
You're standing in front of the spooky old house again. 
It's almost Thanksgiving but their Halloween decorations 
are still up. You think you see a light in the back...?
    )" << endl;

    // These functions (showChoices, getPlayerChoice) are defined in the .cpp
    extern void showChoices(string, string, string);
    extern int getPlayerChoice(int);

    showChoices("Go check the front door.",
                "Walk around back and check the garden.",
                "Forget it and go home.");

    choice = getPlayerChoice(MAX);

    if (choice == 1) {
        front_door_path();
    } else if (choice == 2) {
        garden_path();
    } else if (choice == 3) {
        go_home();
    }
}

void front_door_path() {
    int choice;
    cout << "\n--- THE FRONT DOOR ---" << endl;
    cout << "The porch creaks under your feet. The door is slightly ajar." << endl;
    
    extern void showChoices(string, string, string);
    extern int getPlayerChoice(int);

    showChoices("Knock loudly.", "Kick the door open.", "Run back to the garden.");
    choice = getPlayerChoice(3);

    if (choice == 1) {
        cout << "A ghost answers and offers you tea. You win?" << endl;
    } else if (choice == 2) {
        cout << "The door hits a tripwire! Buckets of glitter fall on you. You're fabulous now." << endl;
    } else {
        garden_path(); // Branch back to the other path
    }
}

void garden_path() {
    int choice;
    cout << "\n--- THE GARDEN ---" << endl;
    cout << "You find a patch of glowing pumpkins. One of them is growling." << endl;

    extern void showChoices(string, string, string);
    extern int getPlayerChoice(int);

    showChoices("Pet the pumpkin.", "Steal the pumpkin.", "Panic and run home.");
    choice = getPlayerChoice(3);

    if (choice == 1) {
        cout << "It purrs! You've made a strange new friend." << endl;
    } else if (choice == 2) {
        cout << "The pumpkin bites your hand! You drop it and flee." << endl;
        go_home();
    } else {
        go_home();
    }
}

void go_home() {
    cout << "\n--- SAFE AT HOME ---" << endl;
    cout << "You decide some things are better left a mystery." << endl;
    cout << "You order a pizza and lock the doors. THE END." << endl;
}

#endif