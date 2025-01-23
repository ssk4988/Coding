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

// {bits, subtree count}
using state = pii;
state combine(state a, state b) {
    int mask = a.first ^ b.first;
    return {mask, a.second + b.second - (__builtin_popcount(a.first) <= 1) + (__builtin_popcount(mask) <= 1)};
}

state decombine(state a, state b) {
    int mask = a.first ^ b.first;
    return {mask, a.second - b.second - (__builtin_popcount(a.first) <= 1) + (__builtin_popcount(mask) <= 1)};
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    string s; cin >> s;
    vvi adj(n);
    rep(i, 0, n-1) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<state> dp(n);
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        dp[u] = {1 << (s[u] - 'A'), 1};
        for(int v : adj[u]) if(v != p) {
            dfs(v, u, dfs);
            dp[u] = combine(dp[u], dp[v]);
        }
    };
    dfs(0, -1, dfs);
    vector<state> reroot(dp);
    auto dfs1 = [&](int u, int p, state parent_dp, auto &&dfs1) -> void {
        if(p != -1) reroot[u] = combine(reroot[u], parent_dp);
        for(int v : adj[u]) if(v != p) {
            dfs1(v, u, decombine(reroot[u], dp[v]), dfs1);
        }
    };
    dfs1(0, -1, {0, 0}, dfs1);
    rep(i, 0, n){
        cout << reroot[i].second << "\n";
    }
    return 0;
}
