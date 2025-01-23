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

using state = pii; // {shortest in subtree, path to root}
state add(state a, state b) {
    auto [long1, paths1] = a;
    auto [long2, paths2] = b;
    long1 = min(long1, long2);
    if(1 + paths2 < paths1) {
        long1 = min(long1, paths1 - 1);
        paths1 = 1 + paths2;
    }
    return {long1, paths1};
}


void solve() {
    int n; cin >> n;
    vvi adj(n);
    rep(i, 0, n-1) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<state> dp(n);
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        dp[u] = {{}, {1}};
        for(int v : adj[u]) if(v != p) {
            dfs(v, u, dfs);
            dp[u] = add(dp[u], dp[v]);
        }
    };
    dfs(0, -1, dfs);
    vector<state> reroot(n);
    auto dfs1 = [&](int u, int p, state parent_dp, auto &&dfs1) -> void {
        vector<pair<int, state>> child;
        if(p != -1) child.emplace_back(p, parent_dp);
        for(int v : adj[u]) if(v != p) {
            child.emplace_back(v, dp[v]);
        }
        vector<state> pref(sz(child)), suff(sz(child));
        
        // reroot[u] = finalize(cur);
        // for(int v : adj[u]) if(v != p) {
        //     dfs1(v, u, finalize(rem(cur, dp_final[v])), dfs1);
        // }
    };
    // dfs1(0, -1, {{}, {}}, dfs1);
    // rep(i, 0, n){
    //     cout << reroot[i].first[0] << " ";
    // }
    // cout << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        solve();
    }
    
    return 0;
}
