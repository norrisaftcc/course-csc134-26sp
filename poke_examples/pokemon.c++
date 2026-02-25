// M3LAB1 - Pokemon Style Demo v2
// Global Variables + Type Matchups!
// CSC 134

#include <iostream>
#include <string>
using namespace std;

// ============================================
// GLOBAL VARIABLES - your starter follows you
// everywhere, just like in the real games!
// ============================================
string starterName = "";
string starterElement = "";
int starterPower = 0;

// Function prototypes
void pick_starter();
void choose_route();
void do_fight(string enemyName, string enemyElement, int enemyHP);
void do_run(string enemyName);
int calculate_matchup(string myElement, string enemyElement);

// ============================================
// main() - Professor Oak's Lab
// ============================================
int main() {

    cout << "=== POCKET MONSTERS: CSC 134 EDITION ===" << endl << endl;
    cout << "PROF. OAK: Welcome to the world of programming!" << endl;
    cout << "Before you head out, you'll need a partner." << endl << endl;

    pick_starter();

    cout << endl;
    cout << "PROF. OAK: Excellent choice! " << starterName << " looks happy!" << endl;
    cout << "Now get out there and explore Route 134!" << endl;

    choose_route();

    cout << endl << "** THANKS FOR PLAYING **" << endl << endl;

    return 0;
}

// ============================================
// Starter selection - SETS the global variables
// ============================================
void pick_starter() {
    int choice;

    cout << "Choose your starter:" << endl;
    cout << "1. BULBASCODE  (Grass type - steady and reliable)" << endl;
    cout << "2. CHARCOMPILE (Fire type  - fast and fierce)" << endl;
    cout << "3. SQUIRTLOOP  (Water type - flexible and cool)" << endl;

    cout << "> ";
    cin >> choice;

    if (choice == 1) {
        starterName = "BULBASCODE";
        starterElement = "Grass";
        starterPower = 12;
        cout << "BULBASCODE nudges your hand gently." << endl;
    }
    else if (choice == 2) {
        starterName = "CHARCOMPILE";
        starterElement = "Fire";
        starterPower = 15;
        cout << "CHARCOMPILE's tail flame flickers excitedly!" << endl;
    }
    else if (choice == 3) {
        starterName = "SQUIRTLOOP";
        starterElement = "Water";
        starterPower = 10;
        cout << "SQUIRTLOOP squirts water at your face. Classic." << endl;
    }
    else {
        starterName = "MISSINGNO";
        starterElement = "Glitch";
        starterPower = 99;
        cout << "Uh... that wasn't one of the options." << endl;
        cout << "A glitchy Pokemon appears in your bag?!" << endl;
    }
}

// ============================================
// Route selection - picks which enemy you face
// ============================================
void choose_route() {
    int choice;

    cout << endl;
    cout << "The path splits into two routes:" << endl;
    cout << "1. Ember Trail   - smells like smoke" << endl;
    cout << "2. Tidal Cavern  - you hear dripping water" << endl;

    cout << "> ";
    cin >> choice;

    if (choice == 1) {
        cout << endl;
        cout << "You walk down Ember Trail..." << endl;
        cout << "The air gets hot. Sparks float around you." << endl;
        cout << "A wild NULLPTR appeared! (Fire type)" << endl << endl;

        cout << "What do you do?" << endl;
        cout << "1. Fight" << endl;
        cout << "2. Run" << endl;
        cout << "> ";
        cin >> choice;

        if (choice == 1) {
            do_fight("NULLPTR", "Fire", 20);
        }
        else {
            do_run("NULLPTR");
        }
    }
    else if (choice == 2) {
        cout << endl;
        cout << "You wade into Tidal Cavern..." << endl;
        cout << "Puddles ripple beneath your feet." << endl;
        cout << "A wild SEGFAULT appeared! (Water type)" << endl << endl;

        cout << "What do you do?" << endl;
        cout << "1. Fight" << endl;
        cout << "2. Run" << endl;
        cout << "> ";
        cin >> choice;

        if (choice == 1) {
            do_fight("SEGFAULT", "Water", 18);
        }
        else {
            do_run("SEGFAULT");
        }
    }
    else {
        cout << "You wander off the path and get lost." << endl;
        cout << "PROF. OAK: This isn't the time to use that!" << endl;
    }
}

// ============================================
// calculate_matchup - the type triangle!
// Returns BONUS DAMAGE based on elements.
//
//   Fire  beats Grass
//   Grass beats Water
//   Water beats Fire
//
// This function doesn't use globals at all -
// it gets everything through its parameters.
// ============================================
int calculate_matchup(string myElement, string enemyElement) {

    // Super effective = bonus damage
    if (myElement == "Fire" && enemyElement == "Grass") {
        cout << "It's super effective!" << endl;
        return 10;
    }
    else if (myElement == "Grass" && enemyElement == "Water") {
        cout << "It's super effective!" << endl;
        return 10;
    }
    else if (myElement == "Water" && enemyElement == "Fire") {
        cout << "It's super effective!" << endl;
        return 10;
    }
    // Not very effective = penalty
    else if (myElement == "Fire" && enemyElement == "Water") {
        cout << "It's not very effective..." << endl;
        return -5;
    }
    else if (myElement == "Grass" && enemyElement == "Fire") {
        cout << "It's not very effective..." << endl;
        return -5;
    }
    else if (myElement == "Water" && enemyElement == "Grass") {
        cout << "It's not very effective..." << endl;
        return -5;
    }
    // Glitch type beats everything (easter egg)
    else if (myElement == "Glitch") {
        cout << "MISSINGNO ignores the type chart!" << endl;
        return 50;
    }
    // Same type or unknown
    else {
        cout << "It's a normal matchup." << endl;
        return 0;
    }
}

// ============================================
// Fight - READS globals + calls calculate_matchup
// ============================================
void do_fight(string enemyName, string enemyElement, int enemyHP) {
    cout << endl;
    cout << "Go, " << starterName << "! (" << starterElement << " type)" << endl;
    cout << starterName << " used TACKLE!" << endl;

    // Call the matchup function to get bonus damage
    int bonus = calculate_matchup(starterElement, enemyElement);
    int totalDamage = starterPower + bonus;

    cout << "Base power: " << starterPower
         << " + Matchup bonus: " << bonus
         << " = Total damage: " << totalDamage << endl;
    cout << enemyName << " HP: " << enemyHP
         << " - " << totalDamage << " = " << (enemyHP - totalDamage) << endl;

    cout << endl;
    if (totalDamage >= enemyHP) {
        cout << "Wild " << enemyName << " fainted!" << endl;
        cout << starterName << " gained 50 EXP!" << endl;
        cout << "[GOOD END - Bug Defeated]" << endl;
    }
    else {
        cout << "Wild " << enemyName << " survived with "
             << (enemyHP - totalDamage) << " HP!" << endl;
        cout << enemyName << " used CRASH! You blacked out!" << endl;
        cout << "[BAD END - Need More Training]" << endl;
    }
}

// ============================================
// Run - READS globals for flavor text
// ============================================
void do_run(string enemyName) {
    cout << endl;
    cout << "You grab " << starterName << " and bolt!" << endl;

    if (starterPower >= 15) {
        cout << starterName << " looks disappointed. It wanted to fight!" << endl;
    }
    else {
        cout << starterName << " seems relieved, honestly." << endl;
    }

    cout << "Got away safely!" << endl;
    cout << "PROF. OAK: The bugs will still be there tomorrow." << endl;
    cout << "[OKAY END - Live to Code Another Day]" << endl;
}