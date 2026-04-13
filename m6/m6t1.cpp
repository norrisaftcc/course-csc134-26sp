/*
M6T1 - Basic Arrays
norrisa
4/13/26
*/

#include <iostream>
using namespace std;

int main() {

    // Set up variables
    const int SIZE = 5; // changing this is the only way to resize the array
    int cars[SIZE];     // contains 5 (SIZE) integers
    double sum = 0;
    double average;
    cout << "This program will ask you to enter a count of cars seen." << endl;
    // first loop: get data
    for (int i=0; i<SIZE; i++) {
        cout << "Day " << i+1 << ": ";
        cin >> cars[i];
    }
    // second loop: sum and average
    for (int i=0; i<SIZE; i++) {
        sum += cars[i]; // add that day's cars
    }
    average = sum / SIZE;
    cout << "Over " << SIZE << " days," << endl;
    cout << "Total cars: " << sum << endl;
    cout << "Average:    " << average << endl;

    // Extra: A simple bar chart
    const int SCALE = 1;  // 1 bar = 1 car
    for (int i = 0; i < SIZE; i++) {
        cout << "DAY " << (i+1) << " | ";
        for (int b = 0; b < cars[i]/SCALE; b++)
            cout << "█";
        cout << " " << cars[i] << "\n";
    }
}