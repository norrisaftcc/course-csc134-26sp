/*
M7T2 
norrisa
4/29/26
Pointer demo, and some rectangles
*/

#include <iostream>
#include "Rectangle.h"
using namespace std;

// Function prototypes
string setName();
void setName(string& name);

int main() {
    // Pointer practice
    // & is Reference (get the address of the data)
    // * is Dereference (get the data from the address)
    string name = "Bob";
    string * pName = &name;     // store the address in a pointer
    //setName(name);
    cout << "name   = " << name << endl;
    cout << "pName  = " << pName << endl;
    cout << "*pName = " << *pName << endl;

    // PART 2 - Rectangles
    Rectangle r1;
    double w, l;
    cout << "Enter width and length, separated by a space: ";
    cin >> w >> l;
    r1.setWidth(w);
    r1.setLength(l);
    cout << "Area is: " << r1.getArea() << endl;
    r1.drawRectangle();


}
// Full Functions
string setName() {
    string name;
    cout << "Enter name: ";
    cin >> name;
    return name;
}
void setName(string& name) {
    cout << "Enter name: ";
    cin >> name;
}