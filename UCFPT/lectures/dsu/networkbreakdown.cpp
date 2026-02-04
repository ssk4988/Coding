#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> par, size;
    int components;
    DSU(int n) : par(n, -1), size(n, 1), components(n) {}
    int find(int x) {
        if(par[x] == -1) return x;
        return par[x] = find(par[x]);
    }
    bool join(int x, int y) {
        x = find(x), y = find(y);
        if(x == y) return false;
        if(size[x] < size[y]) swap(x, y);
        size[x] += size[y];
        par[y] = x;
        components--;
        return true;
    }
};

int main() {
    int n, m, k; cin >> n >> m >> k;
    set<pair<int, int>> edges;
    for(int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        if(u > v) swap(u, v);
        edges.insert({u, v});
    }
    vector<pair<int, int>> deletions(k);
    for(int i = 0; i < k; i++) {
        int u, v; cin >> u >> v;
        u--, v--;
        if(u > v) swap(u, v);
        deletions[i] = {u, v};
        edges.erase({deletions[i]});
    }
    DSU dsu(n);
    for(auto [u, v] : edges) {
        dsu.join(u, v);
    }
    vector<int> ans(k);
    for(int i = k-1; i >= 0; i--) {
        ans[i] = dsu.components;
        dsu.join(deletions[i].first, deletions[i].second);
    }
    for(int i = 0; i < k; i++) {
        cout << ans[i] << " ";
    }
    cout << "\n";
}
