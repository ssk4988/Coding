#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()

using ll = long long;
using vi = vector<int>;
using vl = vector<ll>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

struct Dinic {
    struct Edge {
        int to, rev;
        ll c, oc;
        ll flow() { return max(oc-c, 0LL); }
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
        for(int & i = ptr[v]; i < sz(adj[v]); i++) {
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

void solve() {
    int n; cin >> n;
    vl a(n);
    rep(i, 0, n) cin >> a[i];

    map<ll, int> frq, idx;
    rep(i, 0, n) frq[a[i]]++;

    Dinic flow(2*n + 2);
    int s = 2*n, t = 2*n+1;

    int ptr = 0;
    map<ll, vi> q;
    for(auto [v, f]: frq) {
        idx[v] = ptr;
        flow.addEdge(s, ptr++, f);
        q[v].push_back(v);
    }

    ll res = 0, tot = 0;
    while(sz(q) && tot < n) {
        auto [time, vals] = *q.begin();
        // cout << "TIME: " << time << endl;
        // for(int v: vals) cout << v << ' ';
        // cout << endl;
        q.erase(q.begin());

        flow.addEdge(ptr, t, 1);
        for(ll v: vals)
            flow.addEdge(idx[v], ptr, 1);
        ptr++;

        ll f = flow.calc(s, t);
        tot += f;
        // cout << "FLOW: " << f << '\n';
        
        if(f > 0) {
            res = time;
            for(int v: vals)
                q[time + v].push_back(v);
        }
    }

    cout << res << '\n';
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int t; cin >> t;
    while(t--) solve();

    return 0;
}
