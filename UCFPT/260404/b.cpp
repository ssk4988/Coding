#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>;

struct UF {
    vi e;
    UF(int n): e(n, -1) {}

    int find(int u) { return e[u] < 0 ? u : e[u] = find(e[u]); }
    int size(int u) { return -e[find(u)]; }
    bool join(int u, int v) {
        u = find(u); v = find(v);
        if (u == v) return false;
        e[u] += e[v];
        e[v] = u;
        return true;
    }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        arr[i]--;
    }

    int m;
    cin >> m;

    vector<pair<int, char>> adj;

    vector<char> val(n, 0);
    vector<map<int, char>> prev(n);
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        char c;
        cin >> c;
        x--;
        adj.push_back({x, c});
        prev[x][i] = val[x];
        val[x] = c;
    }

    UF dsu(n);
    for (int i = 0; i < n; i++) {
        if (val[i] == 0) {
            dsu.join(arr[i], i);
        }
    }

    map<char, int> tot;
    for (int i = 0; i < n; i++) {
        if (val[i] != 0) tot[val[i]] += dsu.size(i);
    }

    vector<array<int, 3>> res(m);

    for (int i = m-1; i >= 0; i--) {
        res[i] = {tot['C'], tot['O'], tot['W']};
        int u = adj[i].first;
        tot[val[u]] -= dsu.size(u);
        
        val[u] = prev[u][i];

        if (val[u] != 0) {
            tot[val[u]] += dsu.size(u);
        }
        else {
            int ss = dsu.size(u);
            if (dsu.join(arr[u], u)) {
                tot[val[dsu.find(u)]] += ss;
            }
            else {
                val[dsu.find(u)] = 0;
            }
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < 3; j++) cout << res[i][j] << " ";
        cout << "\n";
    }

    return 0;
}
