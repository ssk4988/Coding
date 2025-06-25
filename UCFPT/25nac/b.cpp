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

const ll mod = 998244353;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vvi adj(n);
    rep(i, 0, n-1) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    auto dfs = [&](int u, int p, auto &&dfs) -> pll {
        bool leaf = u != 0 && sz(adj[u]) == 1;
        pll a{leaf, 1}; // to root, not to root
        for(int v : adj[u]) if(v != p) {
            pll b = dfs(v, u, dfs);
            a.f = (a.s * b.f + a.f * (b.f + b.s)) % mod;
            a.s = (a.s * (b.f + b.s)) % mod;
        }
        // cerr << u << " " << a.f << " " << a.s << " " << leaf << endl;
        return a;
    };
    auto [f, s] = dfs(0, -1, dfs);
    cout << s << "\n";
    
    return 0;
}
