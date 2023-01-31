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

ld eps = 1e-12;

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

ll inf = 1e8;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n; ld r; cin >> n >> r;
        r *= r;
        vvi a(n, vi(4));
        map<vi, int> m;
        int source = 0;
        int sink = 1;
        int cnt = 2;
        int numpeng = 0;
        vector<pair<pi, ll>> edges;
        rep(i, 0, n){
            rep(j, 0, 4){
                cin >> a[i][j];
            }
            m[{i, 0}] = cnt++;
            m[{i, 1}] = cnt++;
            numpeng += a[i][2];
        }
        rep(i, 0, n){
            edges.pb({{source, m[{i, 0}]}, a[i][2]});
            //edges.pb({{m[{i, 0}], sink}, });
            edges.pb({{m[{i, 0}], m[{i, 1}]}, a[i][3]});
            rep(j, 0, n){
                if(i == j) continue;
                if((a[i][0] - a[j][0]) * (a[i][0] - a[j][0]) + (a[i][1] - a[j][1]) * (a[i][1] - a[j][1]) <= r + eps){
                    edges.pb({{m[{i, 1}], m[{j, 0}]}, inf});
                }
            }
        }
        vi ans;
        rep(i, 0, n){
            Dinic d(cnt);
            for(pair<pi, ll> &e : edges){
                d.addEdge(e.f.f, e.f.s, e.s);
            }
            d.addEdge(m[{i, 0}], sink, inf);
            ll mf = d.calc(source, sink);
            assert(mf <= numpeng);
            if(mf == numpeng){
                ans.pb(i);
            }
        }
        if(ans.size() == 0){
            cout << -1 << nL;
        }
        else{
            cout << ans[0];
            rep(i, 1, ans.size()){
                cout << " " << ans[i];
            }
            cout << nL;
        }
    }
    
    return 0;
}
