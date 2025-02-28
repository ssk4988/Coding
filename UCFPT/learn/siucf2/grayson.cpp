#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int g, n; cin >> g >> n;
        vll pos(n);
        vi w(n);
        rep(i, 0, n) {
            cin >> pos[i].f >> pos[i].s >> w[i];
        }
        vector<vector<double>> dp(1 << n, vector<double>(n, 1e18));
        rep(i, 0, n) {
            if(g/5 >= w[i]) dp[1 << i][i] = hypot(pos[i].f, pos[i].s);
        }
        rep(mask, 0, 1 << n) {
            rep(prv, 0, n) {
                if(!((mask >> prv) & 1)) continue;
                int cur = g;
                rep(nxt, 0, n) {
                    if((mask >> nxt)&1) cur += w[nxt];
                }
                rep(nxt, 0, n) {
                    if((mask >> nxt)&1) continue;
                    if(cur/5 < w[nxt]) continue;
                    dp[mask ^ (1 << nxt)][nxt] = min(dp[mask ^ (1 << nxt)][nxt], dp[mask][prv] + hypot(pos[prv].f-pos[nxt].f, pos[nxt].s-pos[prv].s));
                }
            }
        }
        double best = 1e18;
        rep(i, 0, n) best = min(best, dp.back()[i]);
        if(best == 1e18){
            cout << "-1.0\n";
        } else cout << fixed << setprecision(8) << best << "\n";
    }
    
    return 0;
}
