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

void solve() {
    int n, m, k, l;
    cin >> n >> m >> k >> l;

    vi flowers(k);
    vi is_flower(n);
    rep(i, 0, k) {
        cin >> flowers[i], flowers[i]--;
        is_flower[flowers[i]] = true;
    }

    vi is_dest(n);
    rep(i, 0, l) {
        int d; cin >> d;
        is_dest[d-1] = 1;
    }

    vvi adj(n);
    rep(i, 0, m) {
        int u, v; cin >> u >> v; u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vi level(n, -1); level[0] = 0;
    queue<int> q;
    q.push(0);

    rep(i, 0, n) {
        int cur = q.front(); q.pop();
        for(int nxt: adj[cur]) {
            if(level[nxt] != -1) continue;
            level[nxt] = level[cur] + 1;
            q.push(nxt);
        }
    }

    int max_flower = 0;
    vi has_flower(n);
    for(int u: flowers) {
        if(has_flower[level[u]]) {
            cout << string(n-1, '0') << '\n';
            return;
        }
        has_flower[level[u]] = true;
        max_flower = max(max_flower, level[u]);
    }

    vi ord(n); iota(all(ord), 0);
    sort(all(ord), [&](int u, int v) -> bool {
        return level[u] < level[v];
    });

    vi reach_dest(n);
    for(int u: ord | views::reverse) {
        if(level[u] > max_flower && is_dest[u]) {
            reach_dest[u] = true;
            continue;
        }
        if(level[u] == max_flower && is_dest[u] && is_flower[u]) {
            reach_dest[u] = true;
            continue;
        }
        if(has_flower[level[u]] && !is_flower[u]) continue;

        for(int v: adj[u]) if(level[v] == level[u]+1)
            reach_dest[u] |= reach_dest[v];
    }

    vi res(n);
    res[0] = 1;
    for(int u: ord) {
        if(!res[u]) continue;
        for(int v: adj[u]) if(level[v] == level[u]+1) {
            if(has_flower[level[v]] && !is_flower[v]) continue;
            if(!reach_dest[v]) continue;
            res[v] = true;
        }
    }

    rep(i, 1, n) cout << res[i];
    cout << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t; cin >> t;
    while(t--) solve();

    return 0;
}
