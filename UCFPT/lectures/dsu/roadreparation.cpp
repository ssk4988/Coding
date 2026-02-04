#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> par, size;
    DSU(int n) : par(n, -1), size(n, 1) {}
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
        return true;
    }
};

int main() {
    int n, m; cin >> n >> m;
    vector<array<int, 3>> edges(m);
    for(int i = 0; i < m; i++) {
        cin >> edges[i][1] >> edges[i][2] >> edges[i][0];
        edges[i][1]--, edges[i][2]--;
        // {weight, a, b}
    }
    sort(begin(edges), end(edges));
    DSU dsu(n);
    long long ans = 0;
    for(auto [w, a, b] : edges) {
        if(dsu.join(a, b)) ans += w;
    }
    int rep = dsu.find(0);
    if(dsu.size[rep] != n) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << ans << "\n";
    }

    return 0;
}
