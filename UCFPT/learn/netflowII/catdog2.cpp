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
int c, d;

int toInt(string str)
{
    bool cat = str[0] == 'C';
    int id = stoi(str.substr(1))-1;
    if (cat)
        return id;
    return id + c;
}

ll inf = 1e8;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        int v;
        cin >> c >> d >> v;
        int source = 0;
        int sink = 1;
        int cnt = 2;
        map<vi, int> m;
        map<int, vi> rev;
        map<int, int> weight;
        rep(i, 0, c)
        {
            m[{i}] = cnt++;
        }
        rep(i, 0, d)
        {
            m[{c + i}] = cnt++;
        }
        Dinic graph(cnt);
        rep(i, 0, c){
            rep(j, 0, d){
                int j1 = c + j;
                m[{i, j1}] = cnt++;
                m[{j1, i}] = cnt++;
            }
        }
        rep(i, 0, v)
        {
            string str1, str2;
            cin >> str1 >> str2;
            int i1 = toInt(str1), i2 = toInt(str2);
            weight[m[{i1}]]++;
            weight[m[{i2}]]--;
            weight[m[{i1, i2}]]++;
        }
        for (auto &p : m)
        {
            rev[p.s] = p.f;
        }
        ll net = 0;
        for (auto &p : m)
        {
            if (p.f.size() != 1)
            {
                int cs = weight[p.s];
                graph.addEdge(p.f[0], p.f[1], cs);
                net += cs;
            }
            else
            {
                int k = p.f[0];
                int cs = weight[k];
                if (cs > 0)
                {
                    // net += cs; // comment out?
                    graph.addEdge(source, k, inf); // cs
                }
                if (cs < 0)
                {
                    graph.addEdge(k, sink, inf); // abs(cs)
                }
            }
        }
        ll mf = graph.calc(source, sink);
        cout << net << " " << mf << " " << (net - mf) << nL;
    }

    return 0;
}
