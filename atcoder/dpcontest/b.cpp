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
        int n, m; cin >> n >> m;
        vvi adj(n);
        rep(i, 0, m) {
            int u, v; cin >> u >> v; u--, v--;
            adj[u].push_back(v);
        }
        vl dp(n, -1);
        const ll mod = 998244353;
        auto go = [&](int u, auto &&go) -> ll {
            if(dp[u] != -1) return dp[u];
            if(u == n-1) return 1;
            dp[u] = 0;
            for(int v : adj[u]) (dp[u] += go(v, go)) %= mod;
            return dp[u];
        };
        cout << go(0, go) << "\n";
    }
    
    
    return 0;
}
