// M3LAB1 - Lock and Key Demo
// Spooky House CYOA
// CSC 134

#include <iostream>
using namespace std;

// ============================================
// GLOBAL VARIABLE - the "key" in our lock-and-key
// Every function can see this and change it.
// When the player picks up the key, we set it to true.
// When they reach the attic door, we check it.
// ============================================
bool hasKey = false;

// Function prototypes - one for each "room"
void explore_kitchen();
void explore_hallway();
void go_to_basement();
void go_to_attic();

// ============================================
// main() - The front door of the spooky house
// ============================================
int main() {

    int choice;

    cout << "=== THE SPOOKY HOUSE ===" << endl << endl;
    cout << "You stand before an old house on a dare from your friends." << endl;
    cout << "The front door creaks open on its own..." << endl;
    cout << "Inside, you see two doorways:" << endl << endl;
    cout << "1. A dim kitchen with something glinting on the counter" << endl;
    cout << "2. A long dark hallway with stairs at the end" << endl;

    cout << "> ";
    cin >> choice;

    if (1 == choice) {
        explore_kitchen();
    }
    else if (2 == choice) {
        explore_hallway();
    }
    else {
        cout << "You freeze in the doorway. The door slams shut behind you!" << endl;
    }

    cout << endl << "** THE END **" << endl << endl;

    return 0;
}

// ============================================
// Kitchen branch - this is where you GET the key
// ============================================
void explore_kitchen() {
    cout << endl;
    cout << "You step into the kitchen. It smells like dust and old soup." << endl;
    cout << "On the counter, you spot a rusty brass key." << endl;
    cout << "You pocket it. Might be useful." << endl;

    // HERE'S THE MAGIC: we change the global variable
    hasKey = true;

    cout << endl;
    cout << "Now you notice two more paths:" << endl;
    cout << "1. Stairs going DOWN to the basement" << endl;
    cout << "2. Stairs going UP toward the attic" << endl;

    int choice;
    cout << "> ";
    cin >> choice;

    if (choice == 1) {
        go_to_basement();
    }
    else if (choice == 2) {
        go_to_attic();
    }
    else {
        cout << "You stand in the kitchen until sunrise. Anti-climactic." << endl;
    }
}

// ============================================
// Hallway branch - you DON'T get the key here
// ============================================
void explore_hallway() {
    cout << endl;
    cout << "You creep down the hallway. The floorboards groan." << endl;
    cout << "Portraits on the wall seem to watch you." << endl;
    cout << "At the end, you find two staircases:" << endl;
    cout << "1. Stairs going DOWN to the basement" << endl;
    cout << "2. Stairs going UP toward the attic" << endl;

    int choice;
    cout << "> ";
    cin >> choice;

    if (choice == 1) {
        go_to_basement();
    }
    else if (choice == 2) {
        go_to_attic();
    }
    else {
        cout << "You sit in the hallway and question your life choices." << endl;
    }
}

// ============================================
// Basement - bad end no matter what
// ============================================
void go_to_basement() {
    cout << endl;
    cout << "You descend the creaky stairs into darkness..." << endl;
    cout << "Something cold grabs your ankle!" << endl;
    cout << "You scream and run out of the house." << endl;
    cout << "Your friends will never let you live this down." << endl;
    cout << "[BAD END - The Chicken]" << endl;
}

// ============================================
// Attic - good end ONLY if you have the key!
// ============================================
void go_to_attic() {
    cout << endl;
    cout << "You climb the narrow stairs to the attic." << endl;
    cout << "There's a heavy locked door at the top." << endl;

    // HERE'S THE CHECK: we read the global variable
    if (hasKey) {
        cout << "You pull the brass key from your pocket... it fits!" << endl;
        cout << "Inside, you find a dusty treasure chest!" << endl;
        cout << "It's full of old coins and a note that says:" << endl;
        cout << "\"Congratulations, brave explorer!\"" << endl;
        cout << "[GOOD END - The Treasure]" << endl;
    }
    else {
        cout << "The door is locked. You don't have a key." << endl;
        cout << "You bang on it uselessly and then give up." << endl;
        cout << "Should have explored more carefully..." << endl;
        cout << "[BAD END - Locked Out]" << endl;
    }
}