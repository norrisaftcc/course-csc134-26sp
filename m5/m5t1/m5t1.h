#ifndef M5T1_H_INCLUDED
#define M5T1_H_INCLUDED
using namespace std;

// Function declarations (optional in .h)
void say_hi();
int  show_answer();
double square_a_number(double number);


// Function definitions (full code)

void say_hi() {
    cout << "Hello world!" << endl;
    return; // optional, assumed
}

int show_answer() {
    int answer = 42;
    return answer; // return is required because it's not void
}

double square_a_number(double number) {
    // input: a double. output: that double, squared.
    double square = number * number;
    return square;
}


#endif // M5T1_H_INCLUDED
