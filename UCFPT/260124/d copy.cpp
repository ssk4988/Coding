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
    vector<string> grid(2*n-1);
    rep(i, 0, sz(grid)) {
        cin >> grid[i];
    }
    Dinic d((n-1)*(n-1) + 2 * n * n + 2);
    int source = (n-1) * (n-1) + 2 * n * n;
    int sink = source+1;
    int leftedges = 0;
    vi dr{1, 0, -1, 0}, dc{0, 1, 0, -1};
    rep(i, 0, n-1) {
        rep(j, 0, n-1) {
            d.addEdge(source, i*(n-1)+j, 1);
        }
    }
    rep(i, 0, n) {
        rep(j, 0, n) {
            rep(k, 0, 2) {
                d.addEdge((n-1)*(n-1)+i*n*2+j*2+k, sink, 1);
            }
        }
    }
    rep(i, 0, n) {
        rep(j, 0, n) {
            if(i*2+1 < sz(grid) && grid[i*2+1][j*2] == '.') {
                leftedges++;
                for(int j1 = max(0, j-1); j1 < min(n-1, j+1); j1++) {
                    cerr << "connect " << i << " " << j1 << " to " << i << " " << j << " " << 0 << endl;
                    d.addEdge(i*(n-1)+j1, (n-1)*(n-1)+i*n*2+j*2, 1);
                }
            }
            if(j*2+1 < sz(grid[0]) && grid[i*2][j*2+1] == '.') {
                leftedges++;
                for(int i1 = max(0, i-1); i1 < min(n-1, i+1); i1++) {
                    cerr << "connect " << i1 << " " << j << " to " << i << " " << j << " " << 1 << endl;
                    d.addEdge(i1*(n-1)+j, (n-1)*(n-1)+i*n*2+j*2+1, 1);
                }
            }
        }
    }
    ll rem = d.calc(source, sink);
    cerr << "leftedges " << leftedges << " rem " << rem << endl;
    cout << (leftedges - rem)+1 << "\n";
    auto print = [&](int x) {
        x -= (n-1) * (n-1);
        int k = x % 2;
        x /= 2;
        int j = x % n;
        x /= n;
        int i = x % n;
        cerr << i << " " << j << " " << k << " ";
    };
    rep(i, 0, n-1) {
        rep(j, 0, n-1) {
            for(auto &e : d.adj[i*(n-1)+j]) {
                if(e.flow()) {
                    cerr << i << " "<< j << " flows to ";
                    print(e.to);
                    cerr << endl;
                }
            }
        }
    }

    return 0;
}
