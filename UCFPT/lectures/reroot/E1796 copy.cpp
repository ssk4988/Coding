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

using state = pair<vi, vi>; // {shortest in subtree, path to root}

state add(state a, state b) {
    auto [long1, paths1] = a;
    auto [long2, paths2] = b;
    paths1.push_back(1+paths2[0]);
    sort(all(paths1));
    long1.push_back(long2[0]);
    sort(all(long1));
    while(sz(paths1) > 2) paths1.pop_back();
    while(sz(long1) > 2) long1.pop_back();
    return {long1, paths1};
}

state rem(state a, state b) {
    auto [long1, paths1] = a;
    auto [long2, paths2] = b;
    auto it = find(all(long1), long2[0]);
    if(it != end(long1)) long1.erase(it);
    it = find(all(paths1), paths2[0]+1);
    if(it != end(paths1)) paths1.erase(it);
    return {long1, paths1};
}

state finalize(state a) {
    auto [long1, paths1] = a;
    for(int shortest : paths1) {
        long1.push_back(shortest);
    }
    sort(all(long1));
    while(sz(long1) > 2) long1.pop_back();
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
    vector<state> dp(n), dp_final(n);
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        dp[u] = {{}, {}};
        for(int v : adj[u]) if(v != p) {
            dfs(v, u, dfs);
            dp[u] = add(dp[u], dp_final[v]);
        }
        if(sz(dp[u].second) == 0) dp[u].second.push_back(1);
        dp_final[u] = finalize(dp[u]);
    };
    dfs(0, -1, dfs);
    vector<state> reroot(n);
    auto dfs1 = [&](int u, int p, state parent_dp, auto &&dfs1) -> void {
        state cur = dp[u];
        if(p != -1) cur = add(cur, parent_dp);
        reroot[u] = finalize(cur);
        for(int v : adj[u]) if(v != p) {
            dfs1(v, u, finalize(rem(cur, dp_final[v])), dfs1);
        }
    };
    dfs1(0, -1, {{}, {}}, dfs1);
    rep(i, 0, n){
        cout << reroot[i].first[0] << " ";
    }
    cout << "\n";
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
