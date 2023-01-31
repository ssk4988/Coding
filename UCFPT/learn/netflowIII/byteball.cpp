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
    int n, m;
    cin >> n >> m;
    vi points(n);
    vector<vector<bool>> hasPlayed(n, vector<bool>(n, false));
    vector<bool> canWin(n, false);
    rep(i, 0, m){
        int a, b, p, q;
        cin >> a >> b >> p >> q;
        a--;b--;
        hasPlayed[a][b] = hasPlayed[b][a] = true;
        if(p == q){
            points[a]++; points[b]++;
        }
        else if(p > q){
            points[a] += 2;
        }
        else{
            points[b] += 2;
        }
    }
    map<pi, int> label;
    map<int, int> nl, nlrev;
    int source = 0, sink = 1, cnt = 2;
    vvi edges;
    rep(i, 0, n){
        nl[i] = cnt++;
        nlrev[nl[i]] = i;
    }
    rep(i, 0, n){
        rep(j, i + 1, n){
            if(!hasPlayed[i][j]){
                label[{i, j}] = cnt++;
                edges.pb({source, label[{i, j}], 2});
                edges.pb({label[{i, j}], nl[i], 2});
                edges.pb({label[{i, j}], nl[j], 2});
            }
        }
    }

    rep(i, 0, n){
        vi maxPoints(points);
        Dinic d(cnt);
        unordered_set<int> ignore;
        for(auto &v : edges){
            if(v[0] != source && nlrev[v[1]] == i){
                maxPoints[i] += 2;
                ignore.insert(v[0]);
            }
        }
        int gamesLeft = 0;
        for(auto &v : edges){
            if(ignore.find(v[1]) != ignore.end() || ignore.find(v[0]) != ignore.end()){
                continue;
            }
            d.addEdge(v[0], v[1], v[2]);
            if(v[0] == source) gamesLeft++;
        }
        bool good = true;
        rep(j, 0, n){
            if(i == j) continue;
            if(maxPoints[j] > maxPoints[i]){
                good = false;
                break;
            }
            d.addEdge(nl[j], sink, maxPoints[i] - maxPoints[j]);
        }
        if(!good) continue;
        ll mf= d.calc(source, sink);
        assert(mf <= 2 * gamesLeft);
        if(mf == 2 * gamesLeft){
            canWin[i] = true;
        }
    }
    vi ans;
    rep(i, 0, n){
        if(canWin[i]){
            ans.pb(i + 1);
        }
    }
    rep(i ,0, ans.size()){
        cout << ans[i] << (i + 1 < ans.size() ? " " : "\n");
    }


    
    return 0;
}
