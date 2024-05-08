#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main () {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    vvi adj(n);
    vi st;
    rep(i, 0, 2 * n){
        int v; cin >> v;
        if(v > 0){
            st.push_back(v - 1);
        } else{
            v = abs(v) - 1;
            int idx = find(all(st), v) - st.begin();
            for(int j = idx + 1; j < sz(st); j++){
                adj[v].push_back(st[j]);
                adj[st[j]].push_back(v);
            }
            st.erase(find(all(st), v));
        }
    }
    bool works = true;
    vi c(n, -1);
    auto dfs = [&](int u, int t, auto &&dfs) -> void {
        if(c[u] != -1){
            if(c[u] != t) works = false;
            return;
        }
        c[u] = t;
        for(auto v : adj[u]){
            dfs(v, 1 - t, dfs);
        }
    };
    rep(i, 0, n){
        if(c[i] == -1) dfs(i, 0, dfs);
    }
    if(works){
        rep(i, 0, n) cout << "GS"[c[i]];
        cout << "\n";
    } else cout << "*\n";

    return 0;
}
