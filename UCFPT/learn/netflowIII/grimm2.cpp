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
    ll l, r;
    while (true)
    {
        cin >> l >> r;
        if (l == 0 && r == 0)
            break;
        set<ll> fset;
        vector<vl> factors;
        map<ll, int> m, fm;
        int cnt = 0;
        for (ll i = l; i <= r; i++)
        {
            ll i1 = i;
            m[i] = cnt++;
            factors.pb({});
            for (ll k = 2; k * k <= i; k++)
            {
                if (i1 % k == 0)
                {
                    factors.back().pb(k);
                    fset.insert(k);
                    while (i1 % k == 0)
                        i1 /= k;
                }
            }
            if (i1 > 1)
            {
                factors.back().pb(i1);
                fset.insert(i1);
            }
        }
        int firstF = cnt;
        for (ll k : fset)
        {
            fm[k] = cnt++;
        }
        vvi edges;
        int source = cnt++, sink = cnt++;
        rep(i, firstF, source){
            edges.pb({i, sink, 1});
        }
        rep(i, 0, factors.size())
        {
            for (int j : factors[i])
            {
                edges.pb({i, fm[j], 1});
            }
            edges.pb({source, i, 1});
            // edges.pb({i, sink, 1});
        }
        vector<bool> assigned(cnt, false);
        int left = firstF;
        vi matching(firstF);
        rep(i, 0, factors.size())
        {
            int v = m[l + i];
            rep(j, 0, factors[i].size())
            {
                if (assigned[fm[factors[i][j]]])
                    continue;
                int k = fm[factors[i][j]];
                Dinic d(cnt);
                for (auto &q : edges)
                {
                    if (assigned[q[0]] || assigned[q[1]])
                        continue;
                    if (q[0] == k || q[1] == k || q[0] == v || q[1] == v)
                        continue;
                    d.addEdge(q[0], q[1], q[2]);
                }
                ll mf = d.calc(source, sink);
                assert(mf <= left - 1);
                if (mf == left - 1)
                {
                    assigned[k] = true;
                    matching[v] = factors[i][j];
                    break;
                }
            }
            assigned[v] = true;
            left--;
        }
        rep(i, 0, matching.size())
        {
            cout << matching[i];
            if (i + 1 < matching.size())
            {
                cout << " ";
            }
            else
            {
                cout << nL;
            }
        }
    }

    return 0;
}
