#include <bits/stdc++.h>
using namespace std;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

using ll = long long int;
using vi = vector<int>;
using pii = pair<int, int>;
using vvi = vector<vi>;
using vii = vector<pii>;
using ld = long double;
using vl = vector<ll>;

void solve() {
    int n, m, k; cin >> n >> m >> k;
    vl f(m);
    rep(i, 0, m) cin >> f[i];
    vl init(n);
    rep(i, 0, n) cin >> init[i];
    sort(all(f));
    auto calc = [&](ld e) -> ld {
        int under = 0;
        rep(i, 0, m) under += f[i] < e;
        int dunder = 0;
        rep(i, 0, n) {
            dunder += init[i] < e;
        }
        pair<ld, ld> dp{ld(dunder) / n, 1 - ld(dunder) / n};
        cout << fixed << setprecision(10);
        rep(i, 0, 10){
            if(i & 1) {
                dp = {dp.first + dp.second * under / m, dp.second / m * (m - under)};
            } else {
                dp = {dp.first / m * under, dp.second + dp.first / m * (m - under)};
            }
            cout << e << " " << i << " " << (under * dp.first + (m - under) * dp.second) / m << endl;
        }
        return (under * dp.first + (m - under) * dp.second) / m;
    };
    rep(i, 0, 10){
        calc(i);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin.exceptions(cin.failbit);
    // int t;
    // cin >> t;
    // while (t--) 
    solve();

    return 0;
}
