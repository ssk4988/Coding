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
    // int nc; cin >> nc;
    // rep(cn, 0, nc) {
    int n; cin >> n;
    vvi adj(n);
    vi cnt(n);
    {
        string s; cin >> s;
        rep(i, 0, n) {
            cnt[i] = s[i] == '1';
        }
    }
    rep(i, 0, n-1) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }

    vi insub(n), hasdest(n);
    int ans = 0;
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        insub[u] = cnt[u];
        hasdest[u] = u == n-1;
        for(int v : adj[u]) if(v != p) {
            dfs(v, u, dfs);
            insub[u] += insub[v];
            hasdest[u] += hasdest[v];
            if(hasdest[v]) {
                ans += 1;
            } else if(insub[v]) {
                ans += 2;
            }
        }
    };
    dfs(0, -1, dfs);
    cout << ans << "\n";
    // }
    
    return 0;
}
