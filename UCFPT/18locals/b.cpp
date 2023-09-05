#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;

#define sz(x) (int) x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    map<char, int> freq;
    string str; cin >> str;
    for(char c : str) freq[c]++;
    bool alleven = true, allodd = true;
    for(auto [key, val] : freq){
        if(val % 2 == 0){
            allodd = false;
        }
        else alleven = false;
    }
    if(alleven) cout << 0;
    else if(allodd) cout << 1;
    else cout << 2;
    cout << "\n";
}
