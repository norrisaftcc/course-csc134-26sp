// M4T1 - While loops
// csc 134
// norrisa
// 3/4/26

#include <iostream>
using namespace std;

int main() {
    // DEMO - list of numbers and squares
    const int MIN = 1;
    const int MAX = 10;

    int num = MIN;
    int squared; // holds the square

    cout << "Number\tNum Squared" << endl;
    cout << "____________________" << endl;
    while (num <= MAX) {
        squared = num * num;
        cout << num << "\t" << squared << endl; // print number and square
        num++; // next number
    }
}