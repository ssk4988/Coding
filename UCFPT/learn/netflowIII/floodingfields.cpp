#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

struct Dinic
{
    struct Edge
    {
        int to, rev;
        ll c, oc;
        ll flow() { return max(oc - c, 0LL); } // if you need flows
    };
    vi lvl, ptr, q;
    vector<vector<Edge>> adj;
    Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
    void addEdge(int a, int b, ll c, ll rcap = 0)
    {
        // cout << "added " << a << " connection to " << b << nL;
        adj[a].push_back({b, sz(adj[b]), c, c});
        adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
    }
    ll dfs(int v, int t, ll f)
    {
        if (v == t || !f)
            return f;
        for (int &i = ptr[v]; i < sz(adj[v]); i++)
        {
            Edge &e = adj[v][i];
            if (lvl[e.to] == lvl[v] + 1)
                if (ll p = dfs(e.to, t, min(f, e.c)))
                {
                    e.c -= p, adj[e.to][e.rev].c += p;
                    return p;
                }
        }
        return 0;
    }
    ll calc(int s, int t)
    {
        ll flow = 0;
        q[0] = s;
        rep(L, 0, 31) do
        { // 'int L=30' maybe faster for random data
            lvl = ptr = vi(sz(q));
            int qi = 0, qe = lvl[s] = 1;
            while (qi < qe && !lvl[t])
            {
                int v = q[qi++];
                for (Edge e : adj[v])
                    if (!lvl[e.to] && e.c >> (30 - L))
                        q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
            }
            while (ll p = dfs(s, t, LLONG_MAX))
                flow += p;
        }
        while (lvl[t])
            ;
        return flow;
    }
    bool leftOfMinCut(int a) { return lvl[a] != 0; }
};

map<pair<pi, pi>, int> mm;
int cnt = 2, source = 0, sink = 1;

int mget(int i, int j, int k, int l){
    pair<pi, pi> key = {{i, j}, {k, l}};
    if(mm.find(key) == mm.end()){
        return mm[key] = cnt++;
    }
    return mm[key];
}
vvi ds = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}, {0, 0}};
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k, h;
    while (true)
    {
        cin >> n >> k >> h;
        if(n == 0 && k == 0 && h == 0) break;
        cnt = 2, source = 0, sink = 1;
        mm.clear();
        vvi grid(n, vi(n));
        rep(i, 0, n){
            rep(j, 0, n){
                cin >> grid[i][j];
            }
        }
        map<pair<pi, int>, int> inq;
        vvi edges;
        queue<pair<pi, int>> q;
        rep(i, 0, k){
            int r, c; cin >> r >> c;
            int v = mget(r, c, 0, 0);
            edges.pb({source, v, 1});
            q.push({{r, c}, 0});
            inq[{{r, c}, 0}] = 1;
        }
        vi hs(h + 1);
        rep(i, 0, h){
            cin >> hs[i + 1];
        }
        while(!q.empty()){
            auto[p, t] = q.front(); q.pop();
            auto [r, c] = p;
            if(inq[{{r, c}, t}] == 2) continue;
            inq[{{r, c}, t}] = 2;
            int v = mget(r, c, t, 0);
            int v1 = mget(r, c, t, 1);
            edges.pb({v, v1, 1});
            if(t == h){
                edges.pb({v1, sink, 1});
                continue;
            }
            for(int k = 0; k < 5; k++){
                int r1 = r + ds[k][0], c1 = c + ds[k][1], t1 = t + 1;
                if(r1 < 0 || r1 >= n || c1 < 0 || c1 >= n || grid[r1][c1] <= hs[t1]) continue;
                edges.pb({v1, mget(r1, c1, t1, 0), 1});
                pair<pi, int> key = {{r1, c1}, t1};
                if(inq[key] > 0) continue;
                inq[key] = 1;
                q.push(key);
            }
        }

        Dinic d(cnt);
        for(auto &v : edges){
            d.addEdge(v[0], v[1], v[2]);
        }
        ll mf = d.calc(source, sink);
        cout << mf << nL;

    }

    return 0;
}
