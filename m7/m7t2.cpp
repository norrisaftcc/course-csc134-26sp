/*
M7T2 - Rectangles
with some pointer examples also
norrisa
4/29/26
*/
#include <iostream>
using namespace std;

void setName(string &name);

int main() {

    string name = "Bob";
    string * pName = &name; // pointer, which points to address of name

    setName(name);

    cout << "name   = " << name << endl;
    cout << "pName  = " << pName << endl;
    cout << "*pName = " << *pName << endl;


    return 0;
}

void setName(string &name) {
    // uses pass-by-reference, changing the original
    cout << "What's your name? ";
    cin >> name;
}