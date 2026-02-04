#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ll = long long;
using vvi = vector<vi>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vector<set<int>> adj(n);
    rep(i, 0, m) {
        int u, v; cin >> u >> v;
        u--, v--;
        if(adj[u].count(v)) {
            adj[u].erase(v);
        } else 
        adj[v].insert(u);
    }
    pii ans{-1, -1};
    rep(i, 0, n) {
        ans = max(ans, pii{sz(adj[i]), -i});
    }
    cout << -ans.second+1 << " " << ans.first << "\n";

    return 0;
}
