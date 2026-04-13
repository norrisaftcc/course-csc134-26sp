/*
m6t1 - XP Tracker
norrisa
4/13/26
Gather XP per floor, then do stats.
*/

#include <iostream>
using namespace std;

int main() {
    // Set up variables
    const int SIZE = 5; // can only be changed at compile time
    int xp[SIZE];       // fixed size
    double total = 0.0;
    double average;
    int max = 0;
    // Input
    cout << "Dungeon XP Tracker" << endl;
    for (int i=0; i<SIZE; i++) {
        // get XP for floors 1-5
        cout << "Floor " << i+1 << " XP: ";
        cin >> xp[i];
    }

    // Calculation of average and max
    for (int i=0; i<SIZE; i++) {
        // running total
        total += xp[i];
        if (xp[i] > max) {
            max = xp[i]; // if current is larger than max, it's the new max
        }
    }
    average = total / SIZE;
    // Output
    cout << "Over " << SIZE << " Floors" << endl;
    cout << "Total XP: " << total << endl;
    cout << "Avg   XP: " << average << endl;
    cout << "Best  XP: " << max << endl;

    // end program
    return 0;

}