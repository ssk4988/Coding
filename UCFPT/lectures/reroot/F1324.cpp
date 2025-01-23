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

// dp[u] = a[u] + sum of max(0, dp[v])

int add(int root, int child) {
    return root + max(0, child);
}

int rem(int root, int child) {
    return root - max(0, child);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi a(n);
    rep(i, 0, n) {
        cin >> a[i];
        if(a[i] == 0) a[i]--;
    }
    vvi adj(n);
    vi dp(n);
    rep(i, 0, n-1) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u); 
    }
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        dp[u] = a[u];
        for(int v : adj[u]) if(v != p) {
            dfs(v, u, dfs);
            dp[u] = add(dp[u], dp[v]);
        }
    };
    dfs(0, -1, dfs);
    vi reroot(dp);
    auto dfs1 = [&](int u, int p, int parent_dp, auto &&dfs1) -> void {
        if(p != -1) {
            reroot[u] = add(reroot[u], parent_dp);
        }
        for(int v : adj[u]) if(v != p) {
            dfs1(v, u, rem(reroot[u], dp[v]), dfs1);
        }
    };
    dfs1(0, -1, 0, dfs1);
    rep(i, 0, n){
        cout << reroot[i] << " ";
    }
    cout << "\n";
    
    return 0;
}
