/*
CSC 134
M2T2 - Receipt calculator
norrisa
1/26/26
Goal: A correct looking receipt that handles sales tax.
Assumption: Sales tax is 8% (varies by county)
*/

#include <iostream>
using namespace std;
// if you don't use namespace, type std::cout every time instead of cout (also cin)

int main() {
    // Today's roleplay: we're making the receipt printer for a restaurant.
    // Declare all variables
    string meal_name = "Burger Platter";    // change to anything
    int    num_meals;                       // how many they buy
    double meal_price = 5.99;               // $5.99
    double sub_total;                       // price before tax/tips
    double tax_rate = 0.08;                 // 8% is 8/100 ("per cent")
    double tip_amount;
    double tax_amount;                      // $ of the actual tax charged
    double total_price;                     // subtotal + tip + tax


    // Get user input
    cout << "Welcome to the CSC 134 Grill." << endl;
    cout << "Today's Special: " << meal_name << endl;
    cout << endl;
    cout << "How many would you like? ";
    cin  >> num_meals; 
    cout << "Tip amount? (min 0)? ";
    cin  >> tip_amount;

    // Do the calculation
    sub_total = meal_price * num_meals;
    tax_amount = sub_total * tax_rate;  // this much is ADDED to the bill
    // add tax and tips
    total_price = sub_total + tip_amount + tax_amount;

    // Present the output
    cout << endl;
    cout << "YOUR ORDER" << endl << "-----------------------------" << endl;
    cout << num_meals << " x " << meal_name << "\t$" << meal_price << endl;
    cout << "Subtotal: \t\t$" << sub_total << endl;
    cout << "Tip: \t\t\t$" << tip_amount << endl;
    cout << "Tax: \t\t\t$" << tax_amount << endl;
    cout << "-----------------------------" << endl;
    cout << "Total: \t\t\t$" << total_price << endl;
    cout << "THANK YOU COME AGAIN" << endl;

    return 0; // no errors
}

