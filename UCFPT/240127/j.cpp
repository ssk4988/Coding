#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)

using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ll = long long;

char toc(int x){
    if(x < 10) return x + '0';
    x -= 10;
    if(x < 26) return x + 'A';
    x -= 26;
    return x + 'a';
}

int base;

void solve() {
    int n; cin >> n;
    vi lo(n, 0), hi(n, base - 1);
    vi solved(n);
    int moves = __lg(base) + 1;
    rep(_, 0, moves){
        vi test(n);
        rep(i, 0, n){
            int mid = lo[i] + (hi[i] - lo[i]) / 2;
            test[i] = mid;
        }
        rep(i, 0, n){
            cout << toc(test[i]);
        }
        cout << endl;
        string res; cin >> res;
        if(res == "correct") return;
        bool cheat = false;
        rep(i, 0, n){
            if(res[i] == '='){
                lo[i] = hi[i] = test[i];
            }
            else if(solved[i]){
                cheat = true;
                break;
            }
            else if(res[i] == '+'){
                lo[i] = test[i] + 1;
            }
            else{
                hi[i] = test[i] - 1;
            }
        }
        rep(i, 0, n){
            if(lo[i] == hi[i]) solved[i] = true;
            if(lo[i] > hi[i]) cheat = true;
        }
        if(cheat){
            break;
        }
    }
    string res;
    cout << "cheater" << endl;
    cin >> res; 
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> base >> nc;
    rep(cn, 0, nc){
        solve();
    }
    return 0;
}