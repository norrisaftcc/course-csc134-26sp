// M4T1
// CSC 134
// norrisa
// 3/4/26

// Just some while loops

#include <iostream>
using namespace std;

int main() {
    cout << "Part 1: While Loop" << endl;
    int i = 10;
    while (i > 0) {
        i--; // subtract one
        cout << i << " ";
    }
    cout << "done" << endl;
    cout << "Part 2: For Loop" << endl;
    for (int j=0; j<10; j++) {
        cout << j << " ";
    }
    cout << "done" << endl;

    cout << "Part 3: The Table" << endl;
    const int MIN = 1;
    const int MAX = 10;

    int num = MIN; 
    int squared;
    cout << "Number\tNumber Squared\n";
    cout << "----------------------------------" << endl;
    while (num <= MAX) {
        squared = num*num;
        cout << num << "\t" << squared << endl;
        num++; // go to next number
    }

}