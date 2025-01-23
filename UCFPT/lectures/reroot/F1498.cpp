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

// only count if depth % 2k >= k
// add also acts like remove
vi add(vi root, vi child) {
    rep(i, 0, sz(root)) {
        root[(i+1)%sz(root)] ^= child[i];
    }
    return root;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    vvi adj(n);
    rep(i, 0, n-1) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    vvi dp(n, vi(2*k));
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        dp[u][0] = a[u];
        for(int v : adj[u]) if(v != p) {
            dfs(v, u, dfs);
            dp[u] = add(dp[u], dp[v]);
        }
    };
    dfs(0, -1, dfs);
    vvi reroot(dp);
    auto dfs1 = [&](int u, int p, vi parent_dp, auto &&dfs1) -> void {
        if(p != -1) {
            reroot[u] = add(reroot[u], parent_dp);
        }
        for(int v : adj[u]) if(v != p) {
            dfs1(v, u, add(reroot[u], dp[v]), dfs1);
        }
    };
    dfs1(0, -1, vi(), dfs1);
    rep(i, 0, n){
        int ans = 0;
        rep(j, k, 2*k) ans ^= reroot[i][j];
        cout << (ans ? 1 : 0) << " ";
    }
    cout << "\n";
    
    return 0;
}
