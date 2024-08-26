#include <bits/stdc++.h>
using namespace std;

using ld = long double;
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, p; cin >> n >> p;
    vector<string> col(n+1);
    map<string, int> spec;
    set<string> cols;
    rep(i, 1, n){
        cin >> col[i];
        cols.insert(col[i]);
        if(col[i].substr(0, 7) == "SPECIAL"){
            spec[col[i]] = i;
        }
    }
    
    vector<map<string, int>> nxt(n+1);
    for(string c : cols){
        nxt[n][c] = n;
    }
    for(int i = n-1; i >= 0; i--){
        nxt[i] = nxt[i+1];
        if(i != n-1){
            nxt[i][col[i+1]] = i+1;
        }
    }
    int m; cin >> m;
    vector<pair<int, string>> cards(m);
    rep(i, 0, m){
        cin >> cards[i].first >> cards[i].second;
    }
    vi place(p);
    int cur = 0, pidx = 0, turns = 0;
    while(true){
        auto [t, cstr] = cards[cur];
        turns++;
        cur = (cur + 1) % m;
        if(t < 3){
            place[pidx] = nxt[place[pidx]][cstr];
        }
        if(t == 2) {
            place[pidx] = nxt[place[pidx]][cstr];
        }
        if(t == 3){
            place[pidx] = spec[cstr];
        }
        if(place[pidx] == n) break;
        pidx = (pidx + 1) % p;
    }
    cout << 1+pidx << "\n";
    // cout << turns << "\n";
    return 0;
}
