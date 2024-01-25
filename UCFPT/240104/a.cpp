#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int) (x).size()
#define all(x) begin(x), end(x)

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vvi a(n, vi(n)), o(n, vi(n));
    vi r(n), c(n);
    rep(i, 0, n){
        string str; cin >> str;
        rep(j, 0, n){
            a[i][j] = (str[j] == '+' ? 1 : -1);
            if(a[i][j] == -1){
                o[i][j] = 1;
                r[i]++, c[j]++;
            }
        }
    }
    rep(i, 0, n){
        int v; cin >> v;
        r[i] += v;
    }
    rep(j, 0, n){
        int v; cin >> v;
        c[j] += v;
    }
    auto cmp = [&](int a, int b) -> bool { return pii{c[a], a} > pii{c[b], b}; };
    // set<int, decltype(cmp)> s(cmp);
    // rep(i, 0, n){
    //     s.insert(i);
    // }
    rep(i, 0, n){
        vi ord(n);
        iota(all(ord), 0);
        sort(all(ord), cmp);
        rep(j, 0, n){
            if(r[i] > 0){
                int a = ord[j];
                o[i][a] ^= 1;
                r[i]--, c[a]--; 
            }
        }
        // while(r[i] && sz(s)){
        //     int a = *s.begin();
        //     s.erase(s.begin());
        //     rem.push_back(a);
        // }
        // for(int j : rem) s.insert(j);
    }
    bool valid = true;
    rep(i, 0, n){
        if(r[i] != 0 || c[i] != 0) valid = false;
    }
    // rep(i, 0, n) cout << i << " " << r[i] << "\n";
    // rep(i, 0, n) cout << i << " " << c[i] << "\n";
    if(valid){
        cout << "Yes\n";
        rep(i, 0, n){
            rep(j, 0, n){
                cout << o[i][j];
            }
            cout << "\n";
        }
    }
    else{
        cout << "No\n";
    }
    return 0;
}
