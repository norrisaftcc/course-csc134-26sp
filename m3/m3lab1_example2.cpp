// CYOA: The Weird USB Drive
// You found a strange glowing USB drive in the library.
// What do you do with it?

#include <iostream>
using namespace std;

// Function prototypes -- one function per choice
void plugItIn();
void turnItIn();
void sellIt();

int main() {

  int choice;

  // Set the scene -- make it weird
  cout << "You're studying alone in the library basement." << endl;
  cout << "Something is glowing under the table." << endl;
  cout << "It's a USB drive. It's warm. It has no label." << endl;
  cout << "You could swear it just vibrated." << endl;
  cout << endl;

  // Present the choices
  cout << "What do you do?" << endl;
  cout << "1. Plug it into your laptop" << endl;
  cout << "2. Turn it in to campus security" << endl;
  cout << "3. Post it on Discord and sell it" << endl;
  cout << "Enter 1, 2, or 3: ";
  cin >> choice;

  // Branch to the right function
  if (1 == choice) {
    plugItIn();
  }
  else if (2 == choice) {
    turnItIn();
  }
  else if (3 == choice) {
    sellIt();
  }
  else {
    cout << "You leave it there. Smart. Boring, but smart." << endl;
    cout << "...it rolls off the table and follows you out." << endl;
  }

  // Runs no matter what
  cout << endl;
  cout << "You never look at USB drives the same way again." << endl;

  return 0;
}

////
// Define your functions below.
// Go wild -- this is sci-fi/horror, not a resume.
// 3-5 cout lines minimum per function.
// Think: what's the WEIRDEST thing that could happen?
////

void plugItIn() {
  // TODO: What appears on screen? A file? A face? 
  // Does your laptop start doing things on its own?
  // Does it know your name somehow?
  cout << "Your screen flickers..." << endl;
}

void turnItIn() {
  // TODO: How does the security guard react?
  // Do they recognize it? Do they seem scared?
  // Does something happen to THEM when they touch it?
  cout << "The security guard looks at it and goes pale..." << endl;
}

void sellIt() {
  // TODO: Someone in the Discord wants it IMMEDIATELY.
  // How much do they offer? Why do they want it so bad?
  // Do they show up way too fast?
  cout << "Within 30 seconds, someone offers you $500..." << endl;
}