/*
  revenge.cpp
  Pythagorean's Revenge, MCPC 2012 Problem A
  C++ solution by Michael Goldwasser
*/

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

/*
 * Strategy for finding b such that a*a + b*b = c*c relies on fact
 * that a*a = c*c - b*b = (c-b)*(c+b).  So we therefore look for
 * integers x < y such such that x*y = a*a, and then consider
 * b = (y-x)/2 and c = (y+x)/2.
 *
 * We are only interested in cases with b > a. This condition is
 * equivalent to x < a * (sqrt(2) - 1) = a * (0.414...). To avoid use
 * of doubles, we will simply loop while x <= a/2, and verify that
 * b > a for solutions.
 */

ifstream fin("revenge.in");

int main() {
    while (true) {
        long long a;
        fin >> a;
        if (a == 0) break;

        long long count(0);
        for (long long x=1; x <= a/2; x++) {
            if (a*a % x == 0) {
                long long y = a*a / x;
                if ((y-x)%2 == 0) {
                    long long b = (y-x)/2;
                    if (b > a) {
                        count++;
                    }
                }
            }
        }
        cout << count << endl;
    }
}
