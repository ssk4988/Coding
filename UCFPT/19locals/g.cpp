#include <bits/stdc++.h>
using namespace std;

using ld = long double;
using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define rep(i, a, b) for (int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

struct mcmf {
    const ll inf = LLONG_MAX >> 2;
    struct edge {
        int v;
        ll cap, flow, cost;
    };
    int n;
    vector<edge> edges;
    vvi adj; vii par; vi in_q;
    vector<ll> dist, pi;
    mcmf(int n): n(n), adj(n), dist(n), pi(n), par(n), in_q(n) {}
    void add_edge(int u, int v, ll cap, ll cost) {
        int idx = sz(edges);
        edges.push_back({v, cap, 0, cost});
        edges.push_back({u, cap, cap, -cost});
        adj[u].push_back(idx);
        adj[v].push_back(idx ^ 1);
    }
    bool find_path(int s, int t) {
        fill(all(dist), inf);
        fill(all(in_q), 0);
        queue<int> q; q.push(s);
        dist[s] = 0, in_q[s] = 1;
        while(!q.empty()) {
            int cur = q.front(); q.pop();
            in_q[cur] = 0;
            for(int idx : adj[cur]){
                auto [nxt, cap, fl, wt] = edges[idx];
                ll nxtD = dist[cur] + wt;
                if(fl >= cap || nxtD >= dist[nxt]) continue;
                dist[nxt] = nxtD;
                par[nxt] = {cur, idx};
                if(in_q[nxt]) continue;
                q.push(nxt); in_q[nxt] = 1;
            }
        }
        return dist[t] < inf;
    }
    pair<ll, ll> calc(int s, int t) {
        ll flow = 0, cost = 0;
        while(find_path(s, t)) {
            rep(i, 0, n) pi[i] = min(pi[i] + dist[i], inf);
            ll f = inf;
            for(int i, u, v = t; tie(u, i) = par[v], v != s; v = u)
                f = min(f, edges[i].cap - edges[i].flow);
            flow += f;
            for(int i, u, v = t; tie(u, i) = par[v], v != s; v = u)
                edges[i].flow += f, edges[i ^ 1].flow -= f;
        }
        rep(i, 0, sz(edges)>>1)
            cost += edges[i << 1].cost * edges[i << 1].flow;
        return {flow, cost};
    }
};



int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int r, c;
    cin >> r >> c;
    vector<string> grid(r);
    pii bon, cly, tar;
    rep(i, 0, r)
    {
        cin >> grid[i];
        rep(j, 0, c)
        {
            if (grid[i][j] == 'B')
                bon = {i, j};
            else if (grid[i][j] == 'C')
                cly = {i, j};
            else if (grid[i][j] == 'F')
                tar = {i, j};
            // else
        }
    }
    vii dir = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    mcmf f(r * c * 2 + 2);
    int source = r * c * 2, sink = r * c * 2 + 1;
    rep(i, 0, r){
        rep(j, 0, c){
            int cap = grid[i][j] != 'x';
            if(pii{i, j} == tar) cap = 2;
            f.add_edge((i * c + j) * 2, (i * c + j) * 2 + 1, cap, 1);
            for(auto [dr, dc] : dir){
                int i1 = i + dr, j1 = j + dc;
                if(i1 < 0 || j1 < 0 || i1 >= r || j1 >= c) continue;
                f.add_edge((i * c + j) * 2 + 1, (i1 * c + j1) * 2, 1, 0);
            }
        }
    }
    f.add_edge(source, (bon.first * c + bon.second) * 2 + 1, 1, 0);
    f.add_edge(source, (cly.first * c + cly.second) * 2 + 1, 1, 0);
    f.add_edge((tar.first * c + tar.second) * 2 + 1, sink, 2, 0);
    auto [flow, cost] = f.calc(source, sink);
    // cout << flow << " " << cost << "\n";
    if(flow != 2) cout << -1 << "\n";
    else cout << cost << "\n";
    return 0;
}
