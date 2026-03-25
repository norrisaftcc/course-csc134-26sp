// M5T1 - More Functions
// norrisa
// 3/18/26
// Show off different function types

#include <iostream>
#include "m5t1.h"
using namespace std;



// Main() goes here
int main()
{
    say_hi();
    cout << "The answer is: " << show_answer() << endl;
    cout << "Enter a number: ";
    double number;
    cin >> number;
    double answer = square_a_number(number);
    cout << number << " squared is " << answer << endl;
    return 0;
}

