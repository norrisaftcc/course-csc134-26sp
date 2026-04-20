// Happy Birthday for your C++ instructor!
#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
using namespace std;

// Pauses the program for a moment (makes it feel dramatic)
void pause(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

// Prints the birthday cake
void drawCake() {
    cout << "\n";
    cout << "        * * * * * * *        \n";  // candles
    cout << "       | | | | | | |       \n";
    cout << "    ~~~~~~~~~~~~~~~~~~~    \n";  // frosting
    cout << "   |  Happy Birthday!  |   \n";
    cout << "   |                   |   \n";
    cout << "   ~~~~~~~~~~~~~~~~~~~~~   \n";
    cout << "\n";
}

int main() {
    string name = "Mr. Norris";

    // Animated "typing" intro
    vector<string> lines = {
        "Booting up birthday.exe...",
        "Loading confetti module...",
        "Compiling good vibes...",
        "No errors found! Let's go!"
    };

    for (const string& line : lines) {
        cout << line << "\n";
        pause(700);  // wait 700ms between each line
    }

    pause(500);
    drawCake();
    pause(400);

    cout << "  Happy Birthday, " << name << "!\n";
    cout << "  Thank you for teaching us C++.\n";
    cout << "  You make vectors almost make sense. ;)\n\n";

    return 0;
}