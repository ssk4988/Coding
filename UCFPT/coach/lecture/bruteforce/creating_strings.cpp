#include <bits/stdc++.h>
using namespace std;

int n;
string s;
// frequency table of how many of each table we are allowed to use
int freq[26];
vector<string> answer;
// current string we are building
string current;

void bf(int idx) {
    if (idx == n) {
        answer.push_back(current);
        return;
    }
    // try putting every letter at idx
    for(int j = 0; j < 26; j++) {
        if(freq[j] == 0) continue;
        freq[j]--;
        current[idx] = char('a' + j);
        bf(idx+1);
        freq[j]++;
        // current[idx] = 'a'; -- not required since it is overwritten later
    }
}

int main() {
    cin >> s;
    n = s.size();
    current = string(n, 'a');
    for(char c : s) {
        freq[c - 'a']++;
    }

    bf(0);
    cout << answer.size() << "\n";
    for(string x : answer) {
        cout << x << "\n";
    }
}
