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
    int n, k; cin >> n >> k;
    const int inf = 1e6;
    vvi adj(n, vi(n));
    rep(i, 0, n) {
        rep(j, 0, n) cin >> adj[i][j];
    }
    vvi precomp(1 << n, vi(n, inf));
    rep(a, 0, n) {
        rep(i, 1, 1 << n) {
            int b = __lg(i);
            precomp[i][a] = min(precomp[i ^ (1 << b)][a], adj[a][b]);
        }
    }
    vi dp(1 << n, inf);
    rep(i, 0, 1 << n) {
        if(__builtin_popcount(i) == k) {
            dp[i] = 0;
        }
        rep(j, 0, n) {
            if((i >> j) & 1) continue;
            dp[i ^ (1 << j)] = min(dp[i ^ (1 << j)], dp[i] + precomp[i][j]);
        }
    }
    cout << dp.back() << "\n";
    
    
    return 0;
}
