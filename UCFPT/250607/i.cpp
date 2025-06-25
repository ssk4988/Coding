#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

#include <bits/extc++.h>
using namespace __gnu_pbds;
template<class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

struct FT {
    vector<ll> s;
    FT(int n) : s(n) {}
    void update(int pos, ll dif) {
        for(; pos < sz(s); pos |= pos+1) s[pos] += dif;
    }
    ll query(int pos) {
        ll res = 0;
        for(; pos > 0; pos &= pos-1) res += s[pos-1];
        return res;
    }
};


int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vvi adj(n);
    rep(i, 0, n-1) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int T = 0;
    vi tin(n), tout(n);
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        if(p != -1) adj[u].erase(find(all(adj[u]), p));
        tin[u] = T++;
        for(int v : adj[u]) if(v != p) dfs(v, u, dfs);
        tout[u] = T;
    };
    dfs(0, -1, dfs);
    FT ft(n);
    auto tincmp = [&](int x, int y) { return tin[x] < tin[y]; };
    rep(u, 0, n) {
        sort(all(adj[u]), tincmp);
    }
    // rep(u, 0, n) {
    //     cerr << u << " tin " << tin[u] << " tout " << tout[u] << endl;
    // }
    vector<Tree<pii>> sets(n);
    int m; cin >> m;
    vi cost(n);
    rep(i, 0, m) {
        int u, v; cin >> u >> v; u--, v--;
        sets[u].insert({tin[v], i});
        sets[v].insert({tin[u], i});
        cost[v]++;
        cost[u]++;
    }
    auto calccost = [&](int u, int p, auto &&calccost) -> void {
        for(int v : adj[u]) if(v != p) {
            cost[u] += cost[v];
        }
    };
    int q; cin >> q;
    vector<vii> bucket(n);
    rep(i, 0, q) {
        int u, v; cin >> u >> v; u--, v--;
        if(tin[u] < tin[v]) swap(u, v);
        bucket[u].push_back({i, v});
    }
    vi ans(q);
    auto go = [&](int u, int p, auto &&go) -> void {
        for(int v : adj[u]) if(v != p) {
            go(v, u, go);
            if(sz(sets[v]) > sz(sets[u])) sets[u].swap(sets[v]);
        }
        for(int v : adj[u]) if(v != p) {
            // while(sz(sets[v])) sets[u].insert(sets[v].extract(begin(sets[v])));
            for(auto x : sets[v]) {
                sets[u].insert(x);
            }
            sets[v].clear();
        }
        // cerr << "set " << u << ": ";
        // for(auto [x, y] : sets[u]) {
        //     cerr << x << "," << y << " ";
        // }
        // cerr << endl;
        for(auto [i, o] : bucket[u]) {
            if(tin[o] <= tin[u] && tout[u] <= tout[o]) {
                o = *prev(upper_bound(all(adj[o]), u, tincmp));
                ans[i] = sz(sets[u]) - (sets[u].order_of_key({tout[o], -1}) - sets[u].order_of_key({tin[o], -1}));
            } else {
                ans[i] = sets[u].order_of_key({tout[o], -1}) - sets[u].order_of_key({tin[o], -1});
            }
            // cerr << "ans query " << i << " " << o << " " << ans[i] << endl;
        }
    };
    go(0, -1, go);
    rep(i, 0, q) {
        cout << ans[i]+1 << "\n";
    }

    return 0;
}
