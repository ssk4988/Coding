#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    string s; cin >> s;
    map<char, int> freq;
    for(char c : s) freq[c]++;
    vector<pair<int, char>> ps;
    for(auto [key, val] : freq) ps.push_back({-val, key});
    sort(ps.begin(), ps.end());
    for(auto [key, val]  : ps) {
        for(int i = 0; i < -key; i++) cout << val;
    }
    cout << "\n";


    return 0;
}
