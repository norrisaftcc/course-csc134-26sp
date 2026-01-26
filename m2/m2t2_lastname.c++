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
    cout << "Tip amount? (min 0)? "
    

    // Do the calculation
    sub_total = meal_price * num_meals;

    // Present the output
    cout << endl;
    cout << "YOUR ORDER" << endl << "-----------------------------" << endl;
    cout << num_meals << " x " << meal_name << "\t$" << meal_price << endl;
    cout << "Subtotal: \t\t$" << sub_total << endl;

    return 0; // no errors
}

