/*
M6LAB1 - Slime Roulette
norrisa
4/15/26
*/
#include <iostream>
#include <vector>
#include <algorithm>   // std::shuffle
#include <random>      // std::mt19937

using namespace std;

// Function prototypes
void loadMagazine(vector<char>& mag,
                  int slime, int water);
void displayMagazine(const vector<char>& mag);
char fireShot(vector<char>& mag);

// Main()
int main() {
    vector<char> magazine;   // no size yet — grows as needed

    // Now let's test it
    int slime=3;
    int water=2;
    loadMagazine(magazine, slime, water);
    // How full is it? Just ask.
    //cout << "Mag size: " << magazine.size();
    // Show what's loaded
    displayMagazine(magazine); 

    // Fire a shot
    if (!magazine.empty()) {
        char s = fireShot(magazine);
        cout << "You fired: " << s << endl;
    }
    // list again after the shot
    displayMagazine(magazine);
    // What else do we need?
    // Taking turns, dealer and player alternate
    // Hit points (-1 HP from slime)
    // Maybe some items
    // Each round changes what's loaded?
    // and more

    // Basic structure could be:
    // while (playerHP > 0 && dealerHP > 0) is main game loop
    // ask player for action: shoot (s)elf or (d)ealer 
    // (items come later)
    // then fire the shot and process it

    // MAIN GAME LOOP
    int playerHP = 3;
    int dealerHP = 3;
    char choice;
    char shot;
    slime = 1;
    water = 1;
    bool skip_next = false;

    while (playerHP > 0 && dealerHP > 0) {
        cout << "PLAYER: " << playerHP << " HP" << endl;
        cout << "DEALER: " << dealerHP << " HP" << endl;
        loadMagazine(magazine, slime, water);
        displayMagazine(magazine);

        // first, player goes
        cout << "Your turn: fire at (s)elf or (d)ealer: ";
        cin >> choice;
        if (choice == 's' || choice == 'S') {
            // shoot at self
            cout << "You turn the gun on yourself...";
            if (!magazine.empty()) {
            char s = fireShot(magazine);
            if (s == 'S') {
                cout << "SLIMED! (-1hp)\n";
                playerHP -= 1;
            }
            else if (s == 'W') {
                cout << "Water!\n";
                // water on yourself -- skip opponent's turn
                skip_next = true;
            }

        }

        } else {
            // shoot at dealer
        }

        // does gun need to be reloaded?
        if (magazine.empty()) {
            // add 1 to slime or to water
            slime++;
            water++;
            loadMagazine(magazine, slime, water);
            displayMagazine(magazine);
        }

        // then, dealer goes
        if (skip_next) {
            cout << "Skipping dealer's turn..." << endl;
            skip_next = false; 
        } else {
            // dealer shoots
            // random chance dealer shoots self or player: 50/50
            if (choice == 's' || choice == 'S') {
            // shoot at self
            cout << "Dealer aims at themselves...";
            if (!magazine.empty()) {
            char s = fireShot(magazine);
            if (s == 'S') {
                cout << "SLIMED! (-1hp)\n";
                dealerHP -= 1;
            }
            else if (s == 'W') {
                cout << "Water!\n";
                // water on yourself -- skip opponent's turn
                skip_next = true;
            }


            } else {
                // shoot at player
                cout << "Dealer aims at you...";
                if (!magazine.empty()) {
                char s = fireShot(magazine);
                if (s == 'S') {
                    cout << "SLIMED! (-1hp)\n";
                    playerHP -= 1;
                }
                else {
                    cout << "Water!" << endl;
                }
            }

        // does gun need to be reloaded?
        if (magazine.empty()) {
            // add 1 to slime or to water
            slime++;
            water++;
            loadMagazine(magazine, slime, water);
            displayMagazine(magazine);
        }


        }

    }

}

// Full Functions go here
void loadMagazine(vector<char>& mag,
                  int slime, int water) {
    mag.clear();    // fresh start (also handles reload!)

    for (int i = 0; i < slime; i++) mag.push_back('S');
    for (int i = 0; i < water; i++) mag.push_back('W');

    // One line. Properly random. Done.
    random_device rd;
    mt19937 gen(rd());
    shuffle(mag.begin(), mag.end(), gen);

    // Example of how to use fireShot()
    /*
    // Calling code can ask before firing:
    if (!mag.empty()) {
        char s = fireShot(mag);
        // ...
    }
    */
}

void displayMagazine(const vector<char>& mag) {
    int s = 0, w = 0;

    // "for each shell in mag" — no indices, no bounds
    for (char shell : mag) {
        if (shell == 'S') s++;
        else               w++;
    }

    cout << "Magazine: " << mag.size()
         << " remaining ("
         << s << " slime, "
         << w << " water)\n";
}

char fireShot(vector<char>& mag) {
    char shell = mag.back();   // peek the next shell
    mag.pop_back();             // remove it from the magazine
    return shell;
}

