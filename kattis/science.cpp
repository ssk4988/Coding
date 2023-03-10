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
    int n;
    cin >> n;
    vector<vector<bool>> grid(n, vector<bool>(n));
    int source = 2 * n, sink = 2 * n + 1;
    set<pi> edges;
    rep(i, 0, n)
    {
        string str;
        cin >> str;
        edges.insert({source, i});
        rep(j, 0, n)
        {
            grid[i][j] = str[j] == 'Y';
            if (grid[i][j])
                edges.insert({i, j + n});
        }
        // cols edge
        edges.insert({i + n, sink});
    }

    int lo = 0;
    int hi = n;
    while (lo < hi)
    {
        int mid = lo + (hi - lo + 1) / 2;
        Dinic d(sink + 1);
        for (auto &p : edges)
        {
            auto [l, r] = p;
            d.addEdge(l, r, l == source || r == sink ? mid : 1);
        }
        ll mf = d.calc(source, sink);
        assert(mf <= n * mid);
        if(mf == n * mid){
            lo = mid;
        }
        else{
            hi = mid - 1;
        }
    }
    cout << lo << nL;

    source = 0;
    sink = 1;
    int cnt = 2;
    map<pi, int> pt, tb;
    map<vi, int> ptb;
    map<int, vi> revptb;
    rep(i, 0, lo){
        rep(j, 0, n){
            pt[{j, i}] = cnt++;
            tb[{i, j}] = cnt++;
            rep(k, 0, n){
                if(!grid[k][j]) continue;
                ptb[{k, i, j}] = cnt++;
                revptb[ptb[{k, i, j}]] = {k, i, j};
            }
        }
    }
    Dinic d(cnt);
    rep(t, 0, lo){
        rep(p, 0, n){
            d.addEdge(source, pt[{p, t}], 1);
            d.addEdge(tb[{t, p}], sink, 1);
            rep(b, 0, n){
                if(!grid[p][b]) continue;
                d.addEdge(pt[{p, t}], ptb[{p, t, b}], 1);
                d.addEdge(ptb[{p, t, b}], tb[{t, b}], 1);
            }
        }
    }
    ll mf = d.calc(source, sink);
    cout << mf << nL;

    vvi assignments(lo, vi(n));
    rep(t, 0, lo){
        rep(p, 0, n){
            for(auto &e : d.adj[pt[{p, t}]]){
                if(e.flow() > 0){
                    int label = e.to;
                    vi v = revptb[label];
                    int p1 = v[0], t1 = v[1], b = v[2];
                    assert(t == t1);
                    assert(p == p1);
                    assignments[t][b] = p;
                    break;
                }
            }
        }
    }
    // rep(i, 0, lo){
    //     Dinic d(sink + 1);
    //     for (auto &p : edges)
    //     {
    //         auto [l, r] = p;
    //         d.addEdge(l, r, 1);
    //     }
    //     ll mf = d.calc(source, sink);
    //     assignments.pb(vi(n));
    //     rep(j, 0, n){
    //         for(auto &e : d.adj[j]){
    //             if(e.flow() >= 1){
    //                 assignments.back()[e.to - n] = j;
    //                 edges.erase({j, e.to});
    //                 break;
    //             }
    //         }
    //     }
    // }
    rep(i, 0, lo){
        rep(j, 0, n){
            cout << (assignments[i][j] + 1) << (j + 1 < n ? " " : nL);
        }
    }

    return 0;
}
