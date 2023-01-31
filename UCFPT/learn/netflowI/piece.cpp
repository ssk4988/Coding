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
        int n, m;
        cin >> n >> m;
        char grid[n][m];
        // set<pair<pi, pi>> e;
        int cnt = 1;
        int source = 0;
        int sink = n * m * 3;
        Dinic d(n * m * 4);
        // map<pair<pi, pi>, int> el;
        map<pi, int> nl;
        map<vi, int> nl2;
        int bcnt = 0, wcnt = 0;
        rep(i, 0, n)
        {
            string str;
            cin >> str;
            rep(j, 0, m)
            {
                grid[i][j] = str[j];
                // nl[{i, j}] = cnt++;
                if (grid[i][j] == 'B')
                {
                    nl[{i, j}] = cnt++;
                    nl2[{i, j, 0}] = cnt++;
                    nl2[{i, j, 1}] = cnt++;
                    bcnt++;
                    d.addEdge(source, nl[{i, j}], 2);
                }
                if (grid[i][j] == 'W')
                {
                    nl[{i, j}] = cnt++;
                    wcnt++;
                    d.addEdge(nl[{i, j}], sink, 1);
                }
            }
        }
        vector<vvi> dc = {{{1, 0}, {-1, 0}}, {{0, 1}, {0, -1}}};
        rep(i, 0, n)
        {
            rep(j, 0, m)
            {
                if (grid[i][j] == 'B')
                {
                    rep(l, 0, 2)
                    {
                        vi key = {i, j, l};
                        d.addEdge(nl[{i, j}], nl2[key], 1);
                        rep(v, 0, 2)
                        {
                            if (i + dc[l][v][0] >= 0 && i + dc[l][v][0] < n && j + dc[l][v][1] >= 0 && j + dc[l][v][1] < m && grid[i + dc[l][v][0]][j + dc[l][v][1]] == 'W')
                            {
                                // if(nl2.find(key) == nl2.end()){
                                //     nl2[key] = cnt++;
                                // }
                                d.addEdge(nl2[key], nl[{i + dc[l][v][0], j + dc[l][v][1]}], 1);
                            }
                        }
                    }
                }
            }
        }
        ll mf = d.calc(source, sink);
        cout << (mf == 2 * bcnt && mf == wcnt ? "YES" : "NO") << nL;
    }

    return 0;
}
