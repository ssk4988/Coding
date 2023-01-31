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
ll inf = 1e9;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    map<vi, int> m;
    int n;
    cin >> n;
    vector<vector<vector<bool>>> marked(12, vector<vector<bool>>(12, vector<bool>(12)));
    int source = 0;
    int sink = 12 * 12 * 12 + 1;
    int cnt = 1;
    rep(i, 0, n)
    {
        int x, y, z;
        cin >> x >> y >> z;
        x++;
        y++;
        z++;
        marked[x][y][z] = true;
    }
    rep(i, 0, 12)
    {
        rep(j, 0, 12)
        {
            rep(k, 0, 12)
            {
                m[{i, j, k}] = cnt++;
            }
        }
    }
    Dinic d(sink + 1);
    vvi ds;
    rep(i, 0, 3)
    {
        rep(j, 0, 2)
        {

            vi a(3);
            a[i] = j ? -1 : 1;
            ds.pb(a);
        }
    }
    rep(i, 0, 12)
    {
        rep(j, 0, 12)
        {
            rep(k, 0, 12)
            {
                if (marked[i][j][k])
                {
                    d.addEdge(source, m[{i, j, k}], inf);
                }
                else if (i == 0 || j == 0 || k == 0 || i == 11 || j == 11 || k == 11)
                {
                    d.addEdge(m[{i, j, k}], sink, inf);
                }
                rep(l, 0, ds.size())
                {
                    int i1 = i + ds[l][0], j1 = j + ds[l][1], k1 = k + ds[l][2];
                    if (i1 >= 0 && i1 < 12 && j1 >= 0 && j1 < 12 && k1 >= 0 && k1 < 12)
                    {
                        d.addEdge(m[{i, j, k}], m[{i1, j1, k1}], 1);
                    }
                }
            }
        }
    }
    ll mf = d.calc(source, sink);
    cout << mf << nL;

    return 0;
}
