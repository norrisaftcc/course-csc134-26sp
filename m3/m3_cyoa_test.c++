#include <iostream>
#include <string>
#include <limits>

using namespace std;

// --- Function Prototypes ---
// We declare these up here so functions can call each other freely
void startGame();
void sceneArrival();
void sceneFrontDoor();
void scenePeek();

// --- Helper Function for Input ---
int getChoice(int maxChoice) {
    int choice;
    while (true) {
        cout << "\n> ";
        if (cin >> choice && choice >= 1 && choice <= maxChoice) {
            // Clear the input buffer to prevent errors
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }
        cout << "Invalid choice. Please enter a number between 1 and " << maxChoice << "." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// --- Ending Functions ---

void endingCancel() {
    cout << "\n[ENDING: THE COWARD]\n";
    cout << "You cancel the order. Your rating drops to 4.9 stars.\n";
    cout << "You go home and sleep soundly, haunted only by the crushing weight of student loans.\n";
    cout << "GAME OVER.\n";
}

void endingGhost() {
    cout << "\n[ENDING: ECTOPLASMIC SNACK]\n";
    cout << "You eat the Soul Burger. It tastes like static electricity and regret.\n";
    cout << "You turn into a ghost and are now forced to deliver food for eternity.\n";
    cout << "GAME OVER.\n";
}

void endingLawnOrnament() {
    cout << "\n[ENDING: LAWN DECOR]\n";
    cout << "You throw the bag. The burger flies out and hits the ghost in the face.\n";
    cout << "The ghost is not amused. You are now a permanent lawn ornament.\n";
    cout << "GAME OVER.\n";
}

void endingGateDrop() {
    cout << "\n[ENDING: BARE MINIMUM]\n";
    cout << "You leave the food at the gate. As you drive away, you see a shadow float down and pick it up.\n";
    cout << "You get a $2 tip.\n";
    cout << "GAME OVER.\n";
}

void endingRich() {
    cout << "\n[ENDING: EMPLOYEE OF THE MONTH]\n";
    cout << "The ghost smiles (horrifyingly). 'Thank you,' it rasps.\n";
    cout << "'Hard to get service out here since the incident.'\n";
    cout << "He hands you a gold doubloon worth $5,000.\n";
    cout << "YOU WIN!\n";
}

// --- Scene Functions ---

void sceneFrontDoor() {
    cout << "\n----------------------------------------\n";
    cout << "You walk to the porch. The air is freezing. Suddenly, the heavy oak door swings open!\n";
    cout << "A spectral figure floats in the hallway. It looks... hungry.\n";
    
    cout << "1. Throw the bag at the ghost and run!\n";
    cout << "2. Politely say: 'Order for Mr. Ghost?'\n";

    int choice = getChoice(2);

    if (choice == 1) {
        endingLawnOrnament();
    } else {
        endingRich();
    }
}

void sceneArrival() {
    cout << "\n----------------------------------------\n";
    cout << "You arrive at the Old Manor. It's a towering silhouette against the moon.\n";
    cout << "The front gate creaks open automatically. The path is overgrown with thorns.\n";

    cout << "1. Leave the food at the gate and bolt.\n";
    cout << "2. Walk up to the front door like a pro.\n";

    int choice = getChoice(2);

    if (choice == 1) {
        endingGateDrop();
    } else {
        sceneFrontDoor();
    }
}

void scenePeek() {
    cout << "\n----------------------------------------\n";
    cout << "You open the bag. Inside, the burger is glowing with an eerie purple light.\n";
    cout << "It whispers your name. 'STEVE...' (Even if your name isn't Steve). You feel dizzy.\n";

    cout << "1. Close it and drive! I'm getting paid!\n";
    cout << "2. Eat the burger.\n";

    int choice = getChoice(2);

    if (choice == 1) {
        sceneArrival();
    } else {
        endingGhost();
    }
}

void startGame() {
    cout << "\n=================================\n";
    cout << "   THE PHANTOM FOOD DELIVERY     \n";
    cout << "=================================\n";
    cout << "You are a Driver for 'Ecto-Eats'. It's 11:59 PM.\n";
    cout << "You receive an order for a single 'Soul Burger' to be delivered to the Old Manor.\n";
    cout << "Delivery notes: 'DO NOT RING THE BELL. LEAVE IT, OR ELSE.'\n";

    cout << "1. Drive to the Manor immediately.\n";
    cout << "2. Peek inside the bag first.\n";
    cout << "3. Cancel the order. Too spooky.\n";

    int choice = getChoice(3);

    if (choice == 1) {
        sceneArrival();
    } else if (choice == 2) {
        scenePeek();
    } else {
        endingCancel();
    }
}

// --- Main Entry Point ---

int main() {
    startGame();
    return 0;
}