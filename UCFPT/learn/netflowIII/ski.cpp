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
ll inf = 1000000000000LL;

// consider the cells that act as a border, on the inside there is an edge border


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    vvi ds = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    rep(cn, 0, nc){
        //case out adjacent
        int r, c, rr, cr, rt, ct;
        cin >> r >> c >> rr >> cr >> rt >> ct;
        rr--;cr--;rt--;ct--;
        vvi grid(r, vi(c));
        rep(i, 0, r){
            rep(j, 0, c){
                cin >> grid[i][j];
            }
        }
        int source = r * c + 1;
        int sink = r * c + 2;
        Dinic d(r * c + 3);
        bool impossible = false;
        rep(i, 0, r){
            rep(j, 0, c){
                if(i == rt && j == ct) continue;
                int v = i * c + j;
                rep(k, 0, 4){
                    int i1 = i + ds[k][0], j1 = j + ds[k][1];
                    if(i1 < 0 || i1 >= r || j1 < 0 || j1 >= c) continue;
                    if(i == rr && j == cr && i1 == rt && j1 == ct && grid[i][j] >= grid[i1][j1]) impossible = true;
                    if(i1 == rr && j1 == cr) continue;
                    if(grid[i1][j1] > grid[i][j]) continue;
                    int v1 = i1 * c + j1;
                    ll cost = grid[i][j] - grid[i1][j1] + 1;
                    if(i1 == rt && j1 == ct) cost = inf;
                    d.addEdge(v, v1, cost);
                }
            }
        }
        d.addEdge(source, rr * c + cr, 3 * inf);
        d.addEdge(rt * c + ct, sink, 3 * inf);
        ll mf = impossible ? -1 : d.calc(source, sink);
        if(mf == inf) mf = -1;
        cout << mf << nL;
    }
    
    return 0;
}
