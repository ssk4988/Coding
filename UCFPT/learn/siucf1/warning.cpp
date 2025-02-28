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
        int n; cin >> n;
        vl c(n);
        rep(i, 0, n) cin >> c[i];
        vvi adj(n);
        rep(i, 0, n-1) {
            int u, v; cin >> u >> v; u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        auto dfs = [&](int u, int p, int d, auto &&dfs) -> pll {
            pll res{0, c[u]};
            for(int v : adj[u]) if(v != p) {
                auto [c0, c1] = dfs(v, u, d^1, dfs);
                res.first += c1;
                res.second += min(c0, c1);
            }
            return res;
        };
        auto [c0, c1] = dfs(0, -1, 0, dfs);
        cout << min(c0, c1) << "\n";
    }
    
    return 0;
}
