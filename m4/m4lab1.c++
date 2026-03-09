// M4LAB1 - Loop in a loop
// norrisa
// 3/9/26

#include <iostream>
using namespace std;


int main() {
    // char is one character only, uses single quotes
    // char doesn't support Unicode, just plain ASCII
    char symbol = '@';
    string emoji = "✅"; 
    int height = 9;
    int width = 9;

    cout << "Enter height and width (separate with space): ";
    cin >> height >> width;

    // Create a line of emoji symbols
    for (int i=0; i<width; i++ ) {
        cout << emoji << " ";
    }
    cout << endl; // end of line

    for (int i=0; i<height; i++) {
        cout << emoji << endl;
    }
    cout << endl << endl;
    // Finally, build the entire "box"
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            cout << emoji << " ";
        }
        cout << endl;
    }
}