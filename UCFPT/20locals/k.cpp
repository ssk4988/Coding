#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)


const ll mod = 1e9+7;
int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    vvi adj(n);
    rep(i, 0, n-1) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vi log(n);
    int m; cin >> m;
    rep(i, 0, m) {
        int u; cin >> u; u--;
        log[u] = 1;
    }
    // none, redsub, blacksub, blackpar, redpar
    vector<vl> dp(n, vl(5));
    auto dfs = [&](int u, auto &&dfs) -> void {
        if(sz(adj[u]) == 0) {
            dp[u] = {!log[u], 0, 0, log[u], !log[u]};
            return;
        }
        for(int v : adj[u]) {
            adj[v].erase(find(all(adj[v]), u));
            dfs(v, dfs);
        }
        if(log[u]) {
            dp[u][3] = 1;
            vl pref2(sz(adj[u])), suff2(sz(adj[u]));
            ll cur2 = 1;
            rep(i, 0, sz(adj[u])) {
                int v = adj[u][i];
                (dp[u][3] *= dp[v][0] + dp[v][2]) %= mod;
                (cur2 *= dp[v][0] + dp[v][2]) %= mod;
                pref2[i] = cur2;
            }
            cur2 = 1;
            for(int i = sz(adj[u])-1; i >= 0; i--) {
                int v = adj[u][i];
                (cur2 *= dp[v][0] + dp[v][2]) %= mod;
                suff2[i] = cur2;
            }
            rep(i, 0, sz(adj[u])) {
                int v = adj[u][i];
                ll left2 = i > 0 ? pref2[i-1] : 1;
                ll right2 = i + 1 < sz(adj[u]) ? suff2[i+1] : 1;
                (dp[u][2] += (dp[v][4] + dp[v][1]) % mod * left2 % mod * right2) %= mod;
            }
        } else {
            dp[u][0] = 1;
            dp[u][4] = 1;
            dp[u][1] = 1;
            ll sub = 1;
            rep(i, 0, sz(adj[u])) {
                int v = adj[u][i];
                (dp[u][0] *= dp[v][0] + dp[v][1] + dp[v][2]) %= mod;
                (dp[u][4] *= dp[v][0] + dp[v][1]) %= mod;
                (dp[u][1] *= dp[v][0] + dp[v][1] + dp[v][3]) %= mod;
                (sub *= dp[v][0] + dp[v][1]) %= mod;
            }
            (dp[u][1] -= sub) %= mod;
            (dp[u][1] += mod) %= mod;
        }
        // rep(i, 0, 5) cerr << "dp[]" << u << "][" << i << "]=" << dp[u][i] << " " << endl;
    };
    dfs(0, dfs);
    ll ans = (dp[0][0] + dp[0][2] + dp[0][1]) % mod;
    cout << ans << "\n";

    return 0;
}
