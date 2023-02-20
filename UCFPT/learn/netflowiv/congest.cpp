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
    int n, m, c;
    cin >> n >> m >> c;
    vector<unordered_map<int, vi>> e(n);
    vi dist(n, INT_MAX);
    vi start(c);
    vi freq(n);
    rep(i, 0, m)
    {
        int a, b, w;
        cin >> a >> b >> w;
        a--;
        b--;
        e[a][b].pb(w);
        e[b][a].pb(w);
    }
    rep(i, 0, c)
    {
        cin >> start[i];
        start[i]--;
        freq[start[i]]++;
    }
    dist[0] = 0;
    priority_queue<pi> q;
    vector<bool> visited(n);
    q.push({0, 0});
    while (!q.empty())
    {
        pi p = q.top();
        q.pop();
        int i = p.s;
        int t = -p.f;
        if (visited[i])
            continue;
        visited[i] = true;
        for (auto &edge : e[i])
        {
            auto [j, v] = edge;
            for (auto w : v)
            {
                if (!visited[j] && t + w < dist[j])
                {
                    dist[j] = t + w;
                    q.push({-dist[j], j});
                }
            }
        }
    }
    vector<map<int, pi>> opt(n);
    rep(i, 0, n)
    {
        vi er;
        for (auto &edge : e[i])
        {
            int cnt = 0;
            for (int w : edge.s)
            {
                if (dist[i] - dist[edge.f] == w)
                {
                    cnt++;
                }
            }
            if(cnt) opt[i][edge.f] = {dist[i] - dist[edge.f], cnt};
        }
    }
    map<pi, unordered_set<int>> times;
    queue<pi> qbfs;
    rep(i, 0, c)
    {
        qbfs.push({start[i], 0});
    }
    int cnt = n + 1 + 1, source = n, sink = n + 1;
    map<pair<pi, pi>, int> el;
    while (!qbfs.empty())
    {
        auto [a, t] = qbfs.front();
        qbfs.pop();
        for (auto &edge : opt[a])
        {
            auto [b, p1] = edge;
            auto [w, num] = p1;
            auto &es = times[{a, b}];
            if (es.find(t) == es.end())
            {
                es.insert(t);
                qbfs.push({b, t + w});
                rep(i, 0, num){
                    el[{{a, b}, {t, i}}] = cnt++;
                }
            }
        }
    }
    Dinic d(cnt);
    ll mf = freq[0];
    rep(i, 1, n)
    {
        if (freq[i])
        {
            d.addEdge(source, i, freq[i]);
        }
    }
    for (auto &m1 : el)
    {
        auto [m2, label] = m1;
        auto [p1, p2] = m2;
        auto [a, b] = p1;
        auto [t, num] = p2;
        int t1 = t + opt[a][b].f;
        if (t == 0)
        {
            d.addEdge(a, label, 1);
        }
        if (b == 0)
        {
            d.addEdge(label, sink, 1);
        }
        else
        {
            for (auto &edge : opt[b])
            {
                auto [b2, p3] = edge;
                auto [t2, num1] = p3;
                rep(i, 0, num1){
                    d.addEdge(label, el[{{b, b2}, {t1, i}}], 1);
                }
            }
        }
    }

    // duplicate roads?
    mf += d.calc(source, sink);
    cout << mf << nL;

    return 0;
}
