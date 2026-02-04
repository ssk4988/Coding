#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;
using ll = long long;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

struct Dinic {
    struct Edge {
        int to, rev;
        ll c, oc;
        ll flow() { return max(oc - c, 0LL); }
    };
    vi lvl, ptr, q;
    vector<vector<Edge>> adj;
    Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
    void addEdge(int a, int b, ll c, ll rcap = 0) {
        adj[a].push_back({b, sz(adj[b]), c, c});
        adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
    }
    ll dfs(int v, int t, ll f) {
        if(v == t || !f) return f;
        for(int& i = ptr[v]; i < sz(adj[v]); i++) {
            Edge& e = adj[v][i];
            if(lvl[e.to] == lvl[v] + 1)
                if(ll p = dfs(e.to, t, min(f, e.c))) {
                    e.c -= p, adj[e.to][e.rev].c += p;
                    return p;
                }
        }
        return 0;
    }
    ll calc(int s, int t) {
        ll flow = 0; q[0] = s;
        rep(L, 0, 31) do {
            lvl = ptr = vi(sz(q));
            int qi = 0, qe = lvl[s] = 1;
            while(qi < qe && !lvl[t]) {
                int v = q[qi++];
                for(Edge e : adj[v])
                    if(!lvl[e.to] && e.c >> (30-L))
                        q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
            }
            while(ll p = dfs(s, t, LLONG_MAX)) flow += p;
        } while(lvl[t]);
        return flow;
    }
    bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    n--;
    vector<string> grid(2*n+1);
    rep(i, 0, sz(grid)) {
        cin >> grid[i];
    }
    Dinic d(n*n+2+2);
    int source = n*n;
    int sink = source+1;
    int evenout = sink+1;
    int oddout = evenout+1;
    int leftedges = 0;
    vvi outer(n, vi(n)), adj(n, vi(n));
    vi dr{1, 0, -1, 0}, dc{0, 1, 0, -1};
    d.addEdge(source, evenout, 1);
    d.addEdge(oddout, sink, 1);
    rep(i, 0, n) {
        rep(j, 0, n) {
            bool parity = (i + j) % 2 == 1;
            if(parity) d.addEdge(i*n+j, sink, 1);
            else d.addEdge(source, i*n+j, 1);
            rep(k, 0, 4) {
                int i1 = 1+2*i + dr[k], j1 = 1+2*j + dc[k];
                if(grid[i1][j1] != '.') continue;
                // cerr << "edge " << i << " " << j << " dir " << k << endl;
                int i2 = i+dr[k], j2 = j + dc[k];
                if(min(i2, j2) < 0 || max(i2, j2) >= n) {
                    leftedges++;
                    outer[i][j]++;
                    if(parity) d.addEdge(evenout, i*n+j, 1);
                    else d.addEdge(i*n+j, oddout, 1);
                } else{ 
                    adj[i][j]++;
                    if(parity) {
                        leftedges++;
                        d.addEdge(i2*n+j2, i*n+j, 1);
                    }
                }
            }
        }
    }
    ll rem = d.calc(source, sink);
    cerr << "leftedges " << leftedges << " rem " << rem << endl;
    cout << (leftedges - rem)+1 << "\n";

    return 0;
}
