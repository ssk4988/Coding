#include <bits/stdc++.h>
using namespace std;

vector<string> grid;
set<int> rows, cols, d1, d2;
void add(int r, int c) {
    rows.insert(r);
    cols.insert(c);
    d1.insert(r+c);
    d2.insert(r-c);
}
void rem(int r, int c) {
    rows.erase(r);
    cols.erase(c);
    d1.erase(r+c);
    d2.erase(r-c);
}
int ans = 0;

void bf(int r) {
    if(r == 8) {
        ans++;
        return;
    }
    for(int c = 0; c < 8; c++) {
        if(cols.count(c) || d1.count(r+c) || d2.count(r-c) || grid[r][c] == '*') continue;
        add(r, c);
        bf(r+1);
        rem(r, c);
    }
}
int main() {
    grid = vector<string>(8);
    // d1 stores r + c
    // d2 stores r - c
    for(int i = 0; i < 8; i++) {
        cin >> grid[i];
    }
    bf(0);
    cout << ans << "\n";

    return 0;
}
