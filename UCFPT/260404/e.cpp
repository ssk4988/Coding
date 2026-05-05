#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        vector<vector<pair<char, int>>> adj(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            char c;
            cin >> u >> v >> c;
            u--, v--;
            adj[u].push_back({c, v});
            adj[v].push_back({c, u});
        }

        vector<int> dist(n, -1);
        vector<int> q{0};
        dist[0] = 0;
        char lowedge = 'z';
        while (!q.empty()) {
            for (int u : q) {
                for (auto [c, v] : adj[u]) lowedge = min(lowedge, c);
            }
            vector<int> qq;
            for (int u : q) {
                for (auto [c, v] : adj[u]) {
                    if (c == lowedge && dist[v] == -1) {
                        dist[v] = dist[u]+1;
                        qq.push_back(v);
                    }
                }
            }
            swap(q, qq);
        }
        for (int i = 0; i < n; i++) {
            cout << dist[i] << " ";
        }
        cout << "\n";
    }

    return 0;
}
