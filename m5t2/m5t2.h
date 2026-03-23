#ifndef M5T2_H_INCLUDED
#define M5T2_H_INCLUDED

#include <iostream>
#include <fstream>
using namespace std;

int square(int num) {
    // input: a number
    // output: the number, squared
    int answer = num * num;
    return answer;
}

void print_table_line(int first, int second) {
    // input: two numbers
    // effect: prints a line with both numbers
    cout << first << "\t" << second << endl;
}


void write_squares_table(string filename, int start, int finish) {
    // INPUT: filename, first number, last number
    // EFFECT: Writes a table of squares from first to last, to the file.
    ofstream outfile;
    outfile.open(filename);
    if (outfile) {
        for (int i=start; i<=finish; i++) {
            int sq = square(i);
            outfile << i << " " << sq << endl;
        }
        outfile.close();
    }
    else {
        cout << "Could not open file: " << filename << endl;
        return; // Can't continue
    }

}

void read_squares_table(string filename) {
    // INPUT: filename to open
    // EFFECT: print out the data (assuming two numbers per line)
    ifstream infile;
    infile.open(filename);
    if (infile) {
        // file is OK
        cout << "Num" << "\t" << "Square" << endl;
        int num1, num2;
        while (infile >> num1 >> num2) {
            // read two numbers at a time, then print them out
            cout << num1 << "\t" << num2 << endl;
        }
    }
    else {
        // file can't open
        cout << "Error: Could not open " << filename << endl;
        return; // done
    }

}

#endif // M5T2_H_INCLUDED
