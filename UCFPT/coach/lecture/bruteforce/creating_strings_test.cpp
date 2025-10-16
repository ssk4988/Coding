#include <bits/stdc++.h>
using namespace std;

string s;
vector<string> ans;
vector<int> remaining;
void bf(int idx, string &cur) {
    if(idx == s.size()) {
        ans.push_back(cur);
        return;
    }
    for(int i = 0; i < 26; i++) {
        if(remaining[i] == 0) continue;
        remaining[i]--;
        cur[idx] = char('a' + i);
        bf(idx+1, cur);
        remaining[i]++;
    }
}

int main() {

    cin >> s;
    remaining = vector<int>(26);
    for(char c : s) {
        remaining[c-'a']++;
    }
    string cur = s;
    bf(0, cur);
    cout << ans.size() << "\n";
    for(string x : ans) {
        cout << x << "\n";
    }

    return 0;
}
