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

int conv(char c) {
    if('0' <= c && c <= '9') return c - '0';
    if('a' <= c && c <= 'z') return c - 'a' + 10;
    return c - 'A' + 36;
}



int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vvi reward(n, vi(n)), penalty(n, vi(n));
    ll ans = 0;
    rep(i, 0, n){
        string str; cin >> str;
        rep(j, 0, n) penalty[i][j] = conv(str[j]);
    }
    rep(i, 0, n){
        string str; cin >> str;
        rep(j, 0, n) reward[i][j] = conv(str[j]);
        if(reward[i][j] >= penalty[i][j]) {

        }
    }
    Dinic d(n * n + 2);
    int source = n * n, sink = n * n + 1;
    auto get_idx = [&](int r, int c) -> int { return r * n + c; };
    rep(i, 0, n){
        rep(j, 0, n){
            if(i + 1 < n) d.addEdge(get_idx(i, j), get_idx(i+1, j), 1e9, 1e9);
            if(j + 1 < n) d.addEdge(get_idx(i, j), get_idx(i, j+1), 1e9, 1e9);
            d.addEdge(source, get_idx(i, j), reward[i][j]);
            d.addEdge(get_idx(i, j), sink, penalty[i][j]);
        }
    }
    ll mf = d.calc(source, sink);
    ans -= mf;
    cout << ans << "\n";
    return 0;
}