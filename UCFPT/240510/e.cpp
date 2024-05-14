#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;


#define all(x) begin(x), end(x)
#define sz(x) (int) x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vvi adj(n);
    rep(i,0, n-1){
        int a, b; cin >> a >> b; a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vi mark(n);
    rep(i, 0, m){
        int v; cin >> v; v--;
        mark[v] = true;
    }
    auto diam = [&](int u, int p, auto &&diam) -> vi {
        vi best;
        for(int v : adj[u]){
            if(v == p) continue;
            vi res = diam(v, u, diam);
            if(sz(res) > sz(best)) swap(best, res);
        }
        if(sz(best) || mark[u]) best.push_back(u);
        return best;
    };
    vi di = diam(0, -1, diam);
    di = diam(di[0], -1, diam);
    if(sz(di) % 2 == 0){
        cout << "NO\n";
        return 0;
    }
    set<int> ss;
    auto dfs = [&](int u, int p, int d, auto &&dfs)->void {
        if(mark[u]) ss.insert(d);
        for(int v : adj[u]){
            if(v == p) continue;
            dfs(v, u, d+1, dfs);
        }
    };
    dfs(di[sz(di) / 2], -1, 0, dfs);
    if(sz(ss) == 1){
        cout << "YES\n";
        cout << (di[sz(di) / 2] + 1) << "\n";
    } else cout << "NO\n";

    return 0;
}
