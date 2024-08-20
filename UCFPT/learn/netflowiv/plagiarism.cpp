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

void solve(int cn)
{
    // cout << "Case " << (cn + 1) << ":\n";
    int n;
    cin >> n;
    vvi adj1(n);
    rep(i, 0, n - 1)
    {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj1[u].pb(v);
        adj1[v].pb(u);
    }
    int m;
    cin >> m;
    vvi adj2(m);
    rep(i, 0, m - 1)
    {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj2[u].pb(v);
        adj2[v].pb(u);
    }
    bool works = false;
    rep(root, 0, n)
    {
        // cout << root << endl;
        vi subsz1(n, 1), subsz2(m, 1), par1(n), par2(m);
        auto dfs = [&](vvi &adj, vi &par, vi &sub, int u, int p, auto &&dfs) -> void
        {
            par[u] = p;
            for (int v : adj[u])
            {
                if (v == p)
                    continue;
                dfs(adj, par, sub, v, u, dfs);
                sub[u] += sub[v];
            }
        };
        dfs(adj1, par1, subsz1, root, -1, dfs);
        dfs(adj2, par2, subsz2, 0, -1, dfs);
        vvi dp(n, vi(m, -1));
        auto go = [&](int u1, int u2, auto &&go) -> bool
        {
            int &ans = dp[u1][u2];
            if (ans != -1)
                return ans;
            ans = 0;
            vi c1, c2;
            for (int v2 : adj2[u2])
            {
                if (v2 == par2[u2])
                    continue;
                c2.pb(v2);
            }
            for (int v1 : adj1[u1])
            {
                if (v1 == par1[u1])
                    continue;
                c1.pb(v1);
            }
            if (sz(c2) == 0)
            {
                ans = 1;
                // cout << u1 << " " << u2 << " " << ans << " leaf" << endl;
                return ans;
            }
            Dinic d(sz(c1) + sz(c2) + 2);
            int source = sz(c1) + sz(c2);
            int sink = source + 1;
            rep(i, 0, sz(c1))
            {
                d.addEdge(source, i, 1);
                rep(j, 0, sz(c2))
                {
                    if (go(c1[i], c2[j], go))
                        d.addEdge(i, sz(c1) + j, 1);
                }
            }
            rep(i, 0, sz(c2)) d.addEdge(sz(c1) + i, sink, 1);
            ll mf = d.calc(source, sink);
            ans = mf == sz(c2);
            // cout << u1 << " " << u2 << " " << ans << endl;
            return ans;
        };
        if (go(root, 0, go))
        {
            works = true;
        }
    }
    // if(works){
    cout << "Case #" << (cn + 1) << ": " << (works ? "YES" : "NO") << "\n";
    // }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    rep(cn, 0, nc) solve(cn);

    return 0;
}
