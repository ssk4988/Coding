#include <bits/stdc++.h>
using namespace std;

vector<string> grid;

// sets of columns, diagonals, anti-diagonals that have been used already
set<int> col, d1, d2;
// col stores c
// d1 stores r + c
// d2 stores r - c

int ans = 0;

void bt(int r) {
    if(r == 8) {
        ans++;
        return;
    }
    // try placing a queen in each cell in the row
    for(int c = 0; c < 8; c++) {
        if(col.count(c)) continue;
        if(d1.count(r+c)) continue;
        if(d2.count(r-c)) continue;
        if(grid[r][c] == '*') continue;
        // update what we have used
        col.insert(c);
        d1.insert(r+c);
        d2.insert(r-c);
        bt(r+1);
        // we are no longer using these
        col.erase(c);
        d1.erase(r+c);
        d2.erase(r-c);
    }
}

int main() {
    grid = vector<string>(8);
    for(int i = 0; i < 8; i++) {
        cin >> grid[i];
    }

    bt(0);
    cout << ans << "\n";
}
