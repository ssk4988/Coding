/*
  digits.cpp
  Digit Solitaire, MCPC 2012 Problem B
  C++ solution by Michael Goldwasser
*/

#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("digits.in");

int main() {
    while (true) {
        int v;
        fin >> v;
        if (v == 0) break;
        cout << v;                     // initial number; no space
        while (v > 9) {
            // compute the product
            int product(1);
            while (v > 0) {
                product *= v % 10;
                v /= 10;
            }
            cout << " " << product;    // note leading space
            v = product;
        }
        cout << endl;
    }
}
