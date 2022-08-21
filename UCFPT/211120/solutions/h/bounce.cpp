/*
  bounce.cpp
  Bounce, MCPC 2012 Problem H
  C++ solution by Michael Goldwasser
*/

/*
  Algorithm: For every starting point in the top row, trace
  every possible walk of length n to establish the repeating
  pattern. With at most 6 starting positions in the top row,
  and then four subsequent moves, each of which has at most 5
  choices of unused neighbors, there are at most 6*5*5*5*5 = 3750
  possible starting paths.

  Then make an attempt to extend paths using the same pattern,
  such that it is only a success if it reaches bottom, and
  then ends at the top.  Note as well that when reaching the
  bottom row, the very next step must either be rightward, or
  upward-right (assuming that wasn't the previous).

  We will use 64-bit integer to track what locations were already
  used, with location (j,k) mapping to bit: j*(c+1) + k.  For a
  particular pattern, we can rely on a dynamic programming approach
  memoizing a state with a <long long, loc> pair, specifying what
  locations have been used and what location was the most recently
  used. For convenience, we also keep an integer specifying the number
  of used cells, so that we do not need to compute from the bitmap.
  (admittedly, for the judge's inputs, the dynamic programming is
  unnecessary efficiency.)
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

ifstream fin("bounce.in");
int r,c,n;
char grid[7][8];  // we will index as grid[j][k] with 0 <= j < r as row and 0 <= k < c' as column
long long goalUsed;   // will be the minimum bitfield such that row r-1 is touched

// convert j,k pair to appropriate bit within "used" bitfield
int toIndex(int j, int k) {
    return j*(c+1) + k;
}

// see if j,k pair is within grid, given current r,c values
bool isvalid(int j, int k) {
    return (j >= 0) && (j < r) && (k >= 0) && (k < c + j%2);
}

vector<pair<int,int> > hex_neighbors(int j, int k) {
    vector<pair<int, int> > answers;
    int steps[6][2] = { {j-1,k}, {j-1,k+1-(j%2)*2},   // upward
                        {j,k-1}, {j,k+1},             // horizontal
                        {j+1,k}, {j+1,k+1-(j%2)*2}};  // downward
    for (int z=0; z<6; z++) {
        int a(steps[z][0]), b(steps[z][1]);
        if (isvalid(a,b))
            answers.push_back(make_pair(a,b));
    }
    return answers;
}

struct Path {
    string pattern;  // (partial) starting pattern up to n characters long
    int j,k;         // indicies of most recent location used (j=row, k=column)
    int length;      // length of path, thus far
    long long used;  // bitmap of actual cells used with (j,k) -> bit (j*(c+1) + k)

    Path() : pattern(""), length(0), used(0) {}

    Path(int j, int k, const Path& prev=Path()) : j(j), k(k) {
        length = 1 + prev.length;
        used = prev.used | (1LL<<toIndex(j,k));
        pattern = prev.pattern;
        if (pattern.size() < n)
            pattern += grid[j][k];
    }

    // allow for use as a key (assuming patterns are equal)
    bool operator<(const Path& other) const {
        if (used < other.used)
            return true;
        if (used > other.used)
            return false;
        if (j < other.j || (j == other.j && k < other.k));
    }

    vector<Path> neighbors() const {
        vector<Path> answers;
        vector<pair<int,int> > candidates = hex_neighbors(j,k);
        for (int i=0; i < candidates.size(); i++) {
            int a=candidates[i].first;
            int b=candidates[i].second;
            int bit = toIndex(a,b);
            // ensure that (a,b) is unused
            if ((used & (1LL<<bit)) == 0) {
                // ensure that grid[a][b] matches the expected character
                if (length < n || (grid[a][b] == pattern[length%n])) {
                    // ensure that if at bottom, we only allow escape to right of current path (for extra pruning)
                    int trk = k+1-(j%2);  // column of topright neighbor
                    if (j < r-1 || ((a==r-1 && b==k+1) || (a==r-2 && (b==trk || !isvalid(r-2,trk) || (used & (1LL<<toIndex(r-2,trk)) == 0))))) {
                        answers.push_back(Path(a,b,*this));
                    }   
                }                   
            }
        }
        return answers;
    }
};

// store known results for completing current path.
map<Path, string> memory;

// return -1 if unable to complete, else return number of repetitions
// of pattern that were used.
string complete(const Path& current) {
    if (current.length == n)
        memory.clear();        // restart memoization based on current path

    if (current.length > n) {
        map<Path, string>::const_iterator ans = memory.find(current);
        if (ans != memory.end())
            return ans->second;
    }

    string best;

    if (current.pattern.size() == n &&
        current.length % current.pattern.size() == 0 &&
        current.j == 0 &&
        current.used >= goalUsed) {
        // found solution
        while (best.size() < current.length)
            best += current.pattern;
    } else {
        vector<Path> neigh = current.neighbors();
        for (int i=0; i < neigh.size(); i++) {
            string temp = complete(neigh[i]);
            if (temp != "" && (best =="" || temp.size() < best.size()))
                best = temp;
        }
    }

    // memoize
    if (current.length > n) memory[current] = best;
    return best;
}

int main() {
    while (true) {
        fin >> r;
        if (r == 0) break;
        fin >> c >> n;
        // read grid
        for (int j=0; j < r; j++)
            for (int k=0; k < c + j%2; k++)
                fin >> grid[j][k];

        // time to solve the problem
        string shortest;
        goalUsed = (1LL << toIndex(r-1,0));
        for (int k=0; k < c-1; k++) {
            string temp = complete(Path(0,k));
            if (temp != "" && (shortest == "" || temp.size() < shortest.size()))
                shortest = temp;
        }
        if (shortest == "")
            cout << "no solution" << endl;
        else
            cout << shortest << endl;
    }
}
