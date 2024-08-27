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

void solve() {
    int n; cin >> n;
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    vvi adj(n, vi(n));
    vi border(n);
    Dinic original(2*n+2);
    int source = 2*n, sink = 2*n+1;
    rep(i, 0, n){
        string str; cin >> str;
        rep(j, 0, n){
            adj[i][j] = str[j] == 'Y';
            if(a[i] && !a[j] && adj[i][j]) border[i] = true;
        }
        if(a[i]) original.addEdge(source, 2*i, a[i]);
        original.addEdge(2*i, 2*i+1, 1e9);
    }
    rep(i, 0, n){
        rep(j, 0, n){
            if(a[i] && a[j] && adj[i][j]) {
                original.addEdge(2*i, 2*j+1, 1e9);
            }
        }
    }
    int ans = 0;
    for(int dif = 1 << 20; dif; dif /= 2) {
        int cur = ans + dif;
        Dinic d(original);
        ll expect = 0;
        rep(i, 0, n){
            if(border[i]){
                expect += cur;
                d.addEdge(2*i+1, sink, cur);
            } else if(a[i]){
                expect += 1;
                d.addEdge(2*i+1, sink, 1);
            }
        }
        ll mf = d.calc(source, sink);
        // cout << cur << " " << mf << " " << expect << "\n";
        if(mf == expect) ans = cur;
    }
    cout << ans << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    while(nc--) solve();
    
    return 0;
}
