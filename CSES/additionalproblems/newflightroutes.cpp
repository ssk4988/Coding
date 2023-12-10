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

vvi s;
vi val, comp, z, cont;
int Time, ncomps;
template <class G, class F>
int dfs(int j, G &g, F &f)
{
    int low = val[j] = ++Time, x;
    z.push_back(j);
    for (auto e : g[j])
        if (comp[e] < 0)
            low = min(low, val[e] ?: dfs(e, g, f));

    if (low == val[j])
    {
        do
        {
            x = z.back();
            z.pop_back();
            comp[x] = ncomps;
            cont.push_back(x);
        } while (x != j);
        f(cont);
        cont.clear();
        ncomps++;
    }
    return val[j] = low;
}
void addscc(vi v)
{
    s.pb(v);
}
template <class G, class F>
void scc(G &g, F f)
{
    int n = sz(g);
    val.assign(n, 0);
    comp.assign(n, -1);
    Time = ncomps = 0;
    rep(i, 0, n) if (comp[i] < 0) dfs(i, g, f);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m;
    cin >> n >> m;
    vvi adj(n);
    rep(i, 0, m)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
    }
    // int sources = 0, sinks = 0;
    scc(adj, addscc);
    vvi sadj(ncomps), rsadj(ncomps), cadj(ncomps);
    rep(i, 0, ncomps)
    {
        for (int j : s[i])
        {
            for (int k : adj[j])
            {
                sadj[comp[j]].pb(comp[k]);
                rsadj[comp[k]].pb(comp[j]);
                cadj[comp[j]].pb(comp[k]);
                cadj[comp[k]].pb(comp[j]);
            }
        }
    }
    vi sinks, sources, issource(ncomps), issink(ncomps);
    rep(i, 0, ncomps)
    {
        if (sz(sadj) == 0)
        {
            sinks.pb(i);
            issink[i] = true;
        }
        if (sz(rsadj) == 0)
        {
            sources.pb(i);
            issource[i] = true;
        }
    }
    // cout << max(sources, sinks) << nL;
    vpi ans;
    vi mc(ncomps, -1);
    vvi mcsource;
    vvi mcsink;
    auto dfs = [&](int cur, int cm, auto &&dfs) -> void
    {
        if (mc[cur] != -1)
            return;
        mc[cur] = cm;
        if(issource[cur]){
            mcsource[cm].pb(cur);
        }
        if(issink[cur]){
            mcsink[cm].pb(cur);
        }
        for(int nex : cadj[cur]){
            dfs(nex, cm, dfs);
        }
    };
    rep(i, 0, ncomps)
    {
        if (mc[i] != -1)
            continue;
        mcsource.pb({});
        mcsink.pb({});
        dfs(i, sz(mcsource) - 1, dfs);
    }
    int cm = sz(mcsource);
    rep(i, 0, cm){
        int j = (i + 1) % cm;
        ans.pb({mcsink[i].back(), mcsource[j].back()});
        mcsink[i].pop_back();
        mcsource[j].pop_back();
    }
    vi leftsources, leftsinks;
    rep(i, 0, cm){
        for(int j : mcsource[i]) leftsources.pb(j);
        for(int j : mcsink[i]) leftsinks.pb(j);
    }
    int mn = min(sz(leftsources), sz(leftsinks));
    rep(i, 0, mn - 1){
        
    }
    while(sz(leftsources) && sz(leftsinks)){
        while(leftsources.size() > 1 && leftsources.back() == leftsinks.back()){
            swap(leftsources.back(), leftsources[sz(leftsources) - 2]);
        }
        if(leftsources.back() == leftsinks.back()){
            break;
        }
        ans.pb({leftsinks.back(), leftsources.back()});
        leftsinks.pop_back();
        leftsources.pop_back();
    }
    for(int i : leftsinks){
        for(int j : sources){
            if(i != j){
                ans.pb({i, j});
                break;
            }
        }
    }

    return 0;
}
