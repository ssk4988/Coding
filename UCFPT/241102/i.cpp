#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;
using pll = pair<ll, ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int) x.size()
#define rep(i, a, b) for (int i = a; i < (b); i++)

using state = tuple<ll, ll, int, int>; // unweighted, weighted, subsz, tsum
state add(state a, state b, ll w) {
    auto [unweighted, weighted, subsz, tsum] = a;
    auto [unweighted1, weighted1, subsz1, tsum1] = b;
    return {unweighted + unweighted1 + subsz1 * w, weighted + weighted1 + tsum1 * w, subsz + subsz1, tsum + tsum1};
}
state rem(state a, state b, ll w) {
    auto [unweighted, weighted, subsz, tsum] = a;
    auto [unweighted1, weighted1, subsz1, tsum1] = b;
    return {unweighted - unweighted1 - subsz1 * w, weighted - weighted1 - tsum1 * w, subsz - subsz1, tsum - tsum1};
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vl t(n);
    rep(i, 0, n) cin >> t[i];
    vector<vector<pll>> adj(n);
    rep(i, 0, n-1){
        int u, v,  w; cin >> u >> v >> w; u--, v--;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    vector<state> root_ans(n);
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        if(p != -1){
            rep(i, 0, sz(adj[u])){
                if(adj[u][i].first == p) {
                    adj[u].erase(begin(adj[u]) + i);
                    break;
                }
            }
        }
        root_ans[u] = {0, 0, 1, t[u]};
        for(auto [v, w] : adj[u]){
            dfs(v, u, dfs);
            root_ans[u] = add(root_ans[u], root_ans[v], w);
        }
    };
    dfs(0, -1, dfs);
    vector<state> reroot_ans(root_ans);
    auto dfs1 = [&](int u, state p, int pw, auto &&dfs1) -> void {
        reroot_ans[u] = add(reroot_ans[u], p, pw);
        for(auto [v, w] : adj[u]) {
            dfs1(v, rem(reroot_ans[u], root_ans[v], w), w, dfs1);
        }
    };
    dfs1(0, {0, 0, 0, 0}, 0, dfs1);
    rep(u, 0, n){
        auto [unweighted, weighted, subsz, tsum] = reroot_ans[u];
        ll ans = t[u] * unweighted + weighted;
        cout << ans << "\n";
    }
    return 0;
}
