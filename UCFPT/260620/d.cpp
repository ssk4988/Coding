#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

/*
1,2,3,4,6,8,9,12,16,18,24,
1 - 1
2 - 2
3 - 3
4 - 4
5 - 2 3
6 - 6
7 - 4 3
8 - 8
9 - 9
10 - 4 6

1178 numbers under 1e18

*/

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vl res;
    ll lim; cin >> lim;
    auto dfs = [&](ll x, ll mult, auto &&dfs) {
        if(x > lim) return;
        res.push_back(x);
        if(mult == 2) dfs(x*2, 2, dfs);
        dfs(x*3, 3, dfs);
    };
    dfs(1, 2, dfs);
    cout << sz(res) << "\n";
    map<int, vi> make;
    vi p2, p3;
    p2.push_back(1);
    p3.push_back(1);
    rep(i, 0, 5) {
        p2.push_back(p2.back() * 2);
        p3.push_back(p3.back() * 3);
    }
    vi v;
    auto bt = [&](int cur, int e2, int e3, int mv, auto &&bt) -> void {
        if(e3 < 0 || e2 < 0 || max(e3, e2) >= sz(p2)) return;
        int x = p2[e2] * p3[e3];
        v.push_back(x);
        cerr << cur+x << ": ";
        for(auto y : v) cerr << y << ",";
        cerr << endl;
        if(make.count(cur + x)) 
            cerr << "is duplicate" << endl;
        make[cur + x] = v;
        bt(cur + x, e2-1, e3+1, 0, bt);
        v.pop_back();
        if(mv == 0) bt(cur, e2-1, e3, 0, bt);
        bt(cur, e2, e3+1, 1, bt);
    };
    bt(0, 3, 0, 0, bt);
    // for(auto x : res) cout << x << "\n";
    return 0;
}
