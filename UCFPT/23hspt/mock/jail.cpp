#include <bits/stdc++.h>

using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
typedef long long ll;
typedef pair<int, int> pi;
typedef vector<int> vi;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str; int time; cin >> str >> time;
    vi freq(26);
    rep(i, 0, sz(str)){
        freq[str[i] - 'a']++;
    }
    char sepa = 'a';
    rep(i, 0, 26){
        if(freq[i] == 0){
            sepa = (char)('a' + i);
            break;
        }
    }
    rep(i, 0, time){
        cout << str;
        if(i + 1 < time){
            cout << sepa;
        }
        else{
            cout << "\n";
        }
    }
}