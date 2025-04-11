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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m; cin >> n >> m;
    vector<set<int>> adj(n);
    rep(i, 0, m) {
        int u, v; cin >> u >> v;
        u--, v--;
        adj[u].insert(v);
        adj[v].insert(u);
    }
    rep(i, 0, n) adj[i].insert(i);
    map<set<int>, vi> rl;
    rep(i, 0, n) {
        rl[adj[i]].pb(i);
    }
    vi label(n, -1);
    bool works = true;
    int seen = 0;
    for(auto [key, val] : rl) {
        for(int i : val) label[i] = seen;
        seen++;
    }
    vvi adj2(seen);
    for(auto [key, val] : rl) {
        set<int> nxt;
        int lbl = label[val[0]];
        for(int i : key) {
            if(label[i] == lbl) continue;
            nxt.insert(label[i]);
        }
        if(sz(nxt) > 2){
            works = false;
            break;
        }
        for(int j : nxt) {
            adj2[lbl].pb(j);
        }
    }
    if(!works){
        cout << "NO\n";
        return 0;
    }
    vi val(seen, -1);
    auto dfs = [&](int u, int p, int d, auto &&dfs) -> void {
        if(val[u] != -1) return;
        val[u] = d;
        vi pos;
        if(p == -1){
            pos.pb(d-1);
            pos.pb(d+1);
        }else pos.pb(d + (d-val[p]));
        for(int v : adj2[u]) if(v != p) {
            int d1 = pos.back(); pos.pop_back();
            dfs(v, u, d1, dfs);
        }
    };
    dfs(0, -1, 1e6, dfs);
    cout << "YES\n";
    rep(i, 0, n) {
        cout << val[label[i]] << " ";
    }
    cout << "\n";

    return 0;
}
