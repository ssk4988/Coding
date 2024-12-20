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
    int n, m; cin >> n >> m;
    vvi adj(n);
    vi dp(n, -1);
    vi in(n), out(n);
    rep(i, 0, m){
        int u, v; cin >> u >> v; u--, v--;
        adj[u].pb(v);
        out[u]++;
        in[v]++;
    }
    auto go = [&](int u, auto &&go) -> int {
        if(dp[u] != -1) return dp[u];
        int& ans = dp[u];
        ans = 1;
        for(int v : adj[u]) 
        if(out[u] > 1 && in[v] > 1){
            ans = max(ans, 1 + go(v, go));
        }
        return ans;
    };
    int ans = 0;
    rep(i, 0, n){
        ans = max(ans, go(i, go));
    }
    cout << ans << "\n";
    
    return 0;
}
