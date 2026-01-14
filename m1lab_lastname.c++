// CSC 134
// M1LAB - Sales
// name
// 1/14/26
/*
We're selling "foo" -- you decide what that is. 
Tell the user how many you have,
how much each costs,
and what the total would be.

If we have time we'll make it more interactive.
*/

#include <iostream> 
using namespace std;

int main() {
    // Declare variables at the top, it's easier to read
    string item = "bananas"; // change to any thing you want to sell
    int item_count = 100;
    double price_each = 0.79;
    double total_price;

    cout << "Welcome to our " << item << " store." << endl;
    cout << "We have " << item_count << " " << item << "." << endl;
    cout << "They cost $" << price_each << " each." << endl;

    // Calculate the total
    total_price = item_count * price_each;

    cout << "Total price is $" << total_price << endl;

    return 0;
}