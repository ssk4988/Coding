#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ll = long long;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int) x.size()

const ll MOD = 998244353;

ll modpow(ll b, ll p){
    ll ans = 1;
    for(; p; p /= 2, b = b * b % MOD)
        if(p&1) (ans *= b) %= MOD;
    return ans;
}

void solve() {
    int n; cin >> n;
    vvi adj(n);
    vi subsz(n, 1);
    vl sqsubsz(n);
    rep(i, 0, n-1){
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    ll ans = 0;
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        for(int v : adj[u]) if (v != p) {
            dfs(v, u, dfs);
            subsz[u] += subsz[v];
        }
        for(int v : adj[u]) if (v != p) {
            ll othersq = n - subsz[v];
            othersq = othersq * othersq % MOD;
            (ans += (sqsubsz[u] * sqsubsz[v] * 2) % MOD) %= MOD;
            (sqsubsz[u] += sqsubsz[v]) %= MOD;
            ll dubs = 2 * sqsubsz[v] - ll(subsz[v]) * subsz[v];
            dubs = (dubs % MOD + MOD) % MOD;
            (ans += othersq * dubs) %= MOD;
            // cout << u << " to " << v << " adds " << (n-subsz[u]+1) <<  " " << othersq << " " << dubs << " " << dubs * othersq << endl;
        }
        (sqsubsz[u] += ll(subsz[u]) * subsz[u] % MOD) %= MOD;
        // cout << u << " " << subsz[u] << " " << sqsubsz[u] << " " << ans << endl;
    };
    dfs(0, -1, dfs);
    // cout << ans << "\n";
    ll pairs = ll(n)*(n-1)/2;
    pairs %= MOD;
    (ans *= modpow(pairs, MOD-2)) %= MOD;
    (ans *= modpow(pairs, MOD-2)) %= MOD;
    cout << ans << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    int t; cin >> t;
    while (t--) solve();

    return 0;
}
