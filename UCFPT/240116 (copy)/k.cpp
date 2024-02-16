#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using vvi = vector<vi>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, h; cin >> n >> h;
    vvi adj(n);
    rep(i, 0, n - 1){
        int a, b; cin >> a >> b; 
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<pair<int, int>> ans;
    vi leaves;
    auto dfs = [&](int cur, int par, auto &&dfs) -> void {
        int c = 0;
        for(int nex : adj[cur]){
            if(nex == par) continue;
            c++;
            dfs(nex, cur, dfs);
        }
        if(c == 0) leaves.push_back(cur);
    };
    dfs(h, -1, dfs);
    if(sz(adj[h]) == 1){
        leaves.push_back(h);
    }
    int l = (sz(leaves) + 1) / 2;
    rep(i, 0, l){
        ans.push_back({leaves[i], leaves[(i + l) % sz(leaves)]});
    }
    cout << sz(ans) << "\n";
    for(auto [u, v] : ans){
        cout << (u) << " " << (v) << "\n";
    }

    return 0;
}