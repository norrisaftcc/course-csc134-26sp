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

    // 'S' = slime, 'W' = water
    magazine.push_back('S');
    magazine.push_back('W');
    magazine.push_back('S');
    // ... and so on

    // How full is it? Just ask.
    cout << magazine.size();
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

