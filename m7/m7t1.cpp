/*
CSC 134
M7T1 - Restaurant Rating
norrisa
4/27/26

*/

#include <iostream>
using namespace std;

class Restaurant {
    private:
     string name;   // name of the place
     double rating; // 1-5 stars, including half stars

    public:
     Restaurant(string n, double r) {
        // Constructor -- makes new object
        name = n;
        rating = r;
     }

    // Getters and Setters
    void setName(string n) {
        name = n;
    }
    void setRating(double r) {
        rating = r;
    }
    string getName() const {
        return name;
    }
    double getRating() const {
        return rating;
    }
    // display function written by Gemini
        // Displays the restaurant name and its rating visually
    void display() const {
        cout << name << ": ";
        
        // Cast the double to an int to get the number of solid whole stars
        int fullStars = static_cast<int>(rating); 
        
        // Determine if there is a remainder of 0.5 or greater
        bool hasHalfStar = (rating - fullStars) >= 0.5;

        // Print the full star emojis
        for (int i = 0; i < fullStars; i++) {
            cout << "⭐";
        }

        // Print a half-star representation. 
        // Since standard emojis don't have a clean "half star", 
        // we use a sparkle emoji here. You could also use a standard '½' character.
        if (hasHalfStar) {
            cout << "✨";
        }

        // Print the numerical value for clarity at the end
        cout << " (" << rating << "/5)" << endl;
    }


};

int main() {

    cout << "Restaurant Reviews" << endl;

    // Create one restaurant
    Restaurant rest1 = Restaurant("Mi Casita", 4.0);
    cout << rest1.getName() << endl;
    cout << rest1.getRating() << endl;
    rest1.display(); // optional

    // Make another using user input
    Restaurant rest2 = Restaurant("", 0.0);
    string n;
    double r;
    cout << "Enter Restaurant Name: ";
    cin >> n;
    cout << "Rating (1.0 - 5.0): ";
    cin >> r;
    rest2.setName(n);
    rest2.setRating(r);
    cout << rest2.getName() << endl;
    cout << rest2.getRating() << endl;
    rest2.display(); // optional

}