#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

struct Dinic {
    struct Edge {
        int to, rev;
        ll c, oc;
        ll flow() { return max(oc - c, 0LL); }
    };
    vi lvl, ptr, q;
    vector<vector<Edge>> adj;
    Dinic(int n): lvl(n), ptr(n), q(n), adj(n) {}
    void addEdge(int a, int b, ll c, ll rcap = 0) {
        adj[a].push_back({b, sz(adj[b]), c, c});
        adj[b].push_back({a, sz(adj[a])-1, rcap, rcap});
    }
    ll dfs(int v, int t, ll f) {
        if(v == t|| !f) return f;
        for(int &i = ptr[v]; i < sz(adj[v]); i++) {
            Edge &e = adj[v][i];
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
                for(Edge e: adj[v])
                    if(!lvl[e.to] && e.c >> (30 - L))
                        q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
            }
            while(ll p = dfs(s, t, LLONG_MAX)) flow += p;
        } while(lvl[t]);
        return flow;
    }
    bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

double scan() {
    string s; cin >> s;
    return stod(s);
}

const ll OFF = 1e6;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    cout << setprecision(3) << fixed;

    int n, m, w, h; cin >> n >> m >> w >> h;
    vector<double> colors(m);
    rep(i, 0, m) colors[i] = scan();
    vector<double> x(n+1);
    x[0] = 0;
    x[n] = w; 
    rep(i, 1, n) x[i] = scan();

    vector<vector<double>> maxs(n, vector<double>(m)), mins(n, vector<double>(m));
    rep(i, 0, n)
        rep(j, 0, m)
            cin >> mins[i][j];

    rep(i, 0, n)
        rep(j, 0, m)
            cin >> maxs[i][j];

    vector<double> height(n);
    rep(i, 0, n) {
        rep(j, 0, m) {
            maxs[i][j] -= mins[i][j];
            height[i] += mins[i][j];
            colors[j] -= mins[i][j];
        }
        height[i] /= (x[i+1] - x[i]);
    }

    double maxHeight = 0, minHeight = h;
    rep(i, 0, n) {
        minHeight = min(minHeight, height[i]);
        maxHeight = max(maxHeight, height[i]);
    }

    auto test = [&](double lower) -> bool {
        Dinic flow(n + m + 2);
        int s = n+m, t = s+1;
        rep(i, 0, m)
            flow.addEdge(s, i, round(colors[i] * OFF));
        rep(i, 0, m)
            rep(j, 0, n)
                flow.addEdge(i, m+j, round(maxs[j][i] * OFF));
        ll tot = 0;
        rep(j, 0, n) {
            double needed = max(0.0, lower - height[j]) * (x[j+1] - x[j]);
            if(needed < 1e-8) continue;
            flow.addEdge(m+j, t, round(needed * OFF));
            tot += round(needed * OFF);
        }
        return flow.calc(s, t) + 100 >= tot;
    };

    double lo = minHeight, hi = maxHeight;
    rep(iter, 0, 25) {
        double md = (lo + hi) / 2;
        if(test(md))
            lo = md;
        else
            hi = md;
    }

    cout << maxHeight - lo << '\n';

    return 0;
}