#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ll = long long;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int) x.size()

void solve() {
    int n, m, k; cin >> n >> m >> k;
    vi busy(n);
    rep(i, 0, k){
        int v; cin >> v; v--; busy[v] = true;
    }
    vvi adj(n);
    rep(i, 0, m){
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int root = -1;
    rep(i, 0, n){
        if(!busy[i]){
            root = i;
        }
    }
    if(root == -1){
        cout << "No\n";
        return;
    }
    vi ord;
    vvi child(n);
    vi used(n);
    auto dfs = [&](int u, auto &&dfs) -> void {
        if(used[u]) return;
        ord.push_back(u);
        used[u] = true;
        if(!busy[u]) {
            for(int v : adj[u]){
                if(!used[v]){
                    child[u].push_back(v);
                    dfs(v, dfs);
                }
            }
        }
    };
    dfs(root, dfs);
    bool works = true;
    int cnt = 0;
    rep(i, 0, n){
        if(!used[i]) works = false;
        cnt += sz(child[i]) > 0;
    }
    if(!works){
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
    cout << cnt << "\n";
    for(int u : ord){
        if(sz(child[u]) == 0) continue;
        cout << u+1 << " " << sz(child[u]) << " ";
        for(int v : child[u]) cout << v+1 << " ";
        cout << "\n";
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(false);

    // int t; cin >> t;
    // while (t--) 
    solve();

    return 0;
}
