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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        int h, w, b;
        cin >> w >> h >> b;
        vector<vector<bool>> grid(h, vector<bool>(w, true));
        rep(i, 0, b)
        {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            rep(j, x1, x2 + 1)
            {
                rep(k, y1, y2 + 1)
                {
                    grid[k][j] = false;
                }
            }
        }
        Dinic d(h * w * 2 + 2);
        int source = h * w * 2;
        int sink = h * w * 2 + 1;
        vvi ds = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        map<vi, int> m;
        int cnt = 0;
        rep(i, 0, h)
        {
            rep(j, 0, w)
            {
                rep(k, 0, 2)
                {
                    m[{i, j, k}] = cnt++;
                }
            }
        }
        rep(i, 0, h)
        {
            rep(j, 0, w)
            {
                if (!grid[i][j])
                    continue;
                d.addEdge(m[{i, j, 0}], m[{i, j, 1}], 1);
                if (i == 0)
                {
                    d.addEdge(source, m[{i, j, 0}], 1);
                }
                if (i == h - 1)
                {
                    d.addEdge(m[{i, j, 1}], sink, 1);
                }
                rep(k, 0, 4)
                {
                    int i1 = i + ds[k][0], j1 = j + ds[k][1];
                    if (i1 < 0 || j1 < 0 || i1 >= h || j1 >= w || !grid[i1][j1])
                        continue;
                    d.addEdge(m[{i, j, 1}], m[{i1, j1, 0}], 1);
                }
            }
        }
        ll mf = d.calc(source, sink);
        cout << "Case #" << (cn + 1) << ": " << mf << nL;
    }

    return 0;
}
