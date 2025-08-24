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
            adj[u].pb(v);adj[v].pb(u);
        }
        if(m > n-1) {
            cout << "0\n";
            continue;
        }
        if(n == 2) {
            cout << "2\n";
            continue;
        }
        const ll mod = 1e9+7;
        vl fact(n+1);
        fact[0] = 1;
        rep(i, 1, sz(fact)) {
            fact[i] = fact[i-1] * i % mod;
        }
        int internal = -1;
        rep(i, 0, n) if(sz(adj[i]) > 1) internal = i;
        assert(internal != -1);
        ll ans = 2;
        auto dfs = [&](int u, int p, auto &&dfs) -> void {
            // cerr << "vis " << u << " " << p << endl;
            // if(p == -1) {

                // (ans *= fact[sz(adj[u])]) %= mod;
            // }
            // else (ans *= fact[sz(adj[u])-1]) %= mod;
            int nonleaf = 0, leaf = 0, nonleafp = 0;
            for(int v : adj[u]) {
                if(v != p) dfs(v, u, dfs);
                if(sz(adj[v]) > 1) nonleaf++;
                else leaf++;
                if(sz(adj[v]) > 1 && p != v) nonleafp++;
            }
            if(nonleafp > 2 || (p != -1 && nonleafp > 1)) {
                ans = 0;
            }
            if(p == -1 && nonleafp > 0) (ans *= 2) %= mod;
            (ans *= fact[leaf]) %= mod;
            // cerr << u << " " << p << " " << leaf << endl;
        };
        dfs(internal, -1, dfs);
        cout << ans << "\n";
    }
    
    return 0;
}
