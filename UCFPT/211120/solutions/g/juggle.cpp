/*
  juggle.cpp
  JuggleFest, MCPC 2012 Problem G
  C++ solution by Michael Goldwasser
*/

#include <iostream>
#include <fstream>
using namespace std;

#define MAX_PERIOD 7
#define NUM_THROWS 20

ifstream fin("juggle.in");

int main() {
    while (true) {
        int P;
        fin >> P;
        if (P == 0) break;

        int pattern[MAX_PERIOD];
        for (int j=0; j < P; j++)
            fin >> pattern[j];

        string answer(20,'_');
        bool valid(true);
        int balls(0);
        for (int k=0; valid && k < NUM_THROWS; k++) {
            if (answer[k] == '_') {
                answer[k] = 'A' + balls++;     // start a new ball here
            }
            // forecast next occurrence of current ball
            int next = k + pattern[k % P];
            if (next < NUM_THROWS) {
                if (answer[next] == '_')
                    answer[next] = answer[k];
                else
                    valid = false;            // CRASH!!!!
            }
        }
        
        if (valid)
            cout << answer << endl;
        else
            cout << "CRASH" << endl;
    }
}
