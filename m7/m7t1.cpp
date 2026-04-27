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

};

int main() {

    cout << "Restaurant Reviews" << endl;
    
}