// M5LAB2
// Header goes here

#include <iostream>
using namespace std;

// Declare (Write the prototypes for)
// the getLength,
// getWidth, getArea, and displayData
// functions here.
double getLength();
double getWidth();
double getArea(double length, double width);
void   displayData(double length, double width, double area);

int main()
{
	// This program calculates the area of a rectangle.
	// TODO: fix any syntax errors
	
   double length,    // The rectangle's length
          width,     // The rectangle's width
          area;      // The rectangle's area
          
   // Get the rectangle's length.
   length = getLength();
   
   // Get the rectangle's width.
   width = getWidth()
   
   // Get the rectangle's area.
   area = getArea();
   
   // Display the rectangle's data.
   displayData(length, width, area);
          
   return 0;
}

//***************************************************
// TODO: write the getLength, getWidth, getArea,    *
// and displayData functions below.                 *
//***************************************************
double getLength() {
    // getLength - Asks the user to enter a rectangle's length, and return that value as a double
    double length;
    cout << "Rectangle length: ";
    cin >> length;
    return length;
}
double getWidth() {
    // getWidth - Asks the user to enter a rectangle's width, and return that value as a double
}
double getArea(double length, double width) {
    // getArea - This function should take two arguments, length and width. It will calculate the area and return that value as a double.
}
void   displayData(double length, double width, double area) {
    // displayData - This function should take three arguments, length, width, and area. It will then display these values as well formatted output. 
}