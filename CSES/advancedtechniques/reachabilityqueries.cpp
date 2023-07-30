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

const int maxn = 50002;

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
    int n, m, q;
    cin >> n >> m >> q;
    vvi adj(n);
    rep(i, 0, m)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].pb(b);
    }
    vvi sccs;
    scc(adj, [&](vi val) -> void
        { sccs.pb(val); });
    vi rev(n);
    rep(i, 0, sz(sccs))
    {
        for (int j : sccs[i])
        {
            rev[j] = i;
        }
    }
    vector<bitset<maxn>> ans(sz(sccs));
    auto dfs = [&](int cur, auto &&dfs) -> bitset<maxn>
    {
        if (ans[cur].any())
            return ans[cur];
        ans[cur].set(cur);
        for (int i : sccs[cur])
        {
            // ans[cur].set(i);
            for (int nex : adj[i]) if(rev[nex] != cur)
                ans[cur] |= dfs(rev[nex], dfs);
        }
        return ans[cur];
    };
    rep(i, 0, sz(sccs)) dfs(i, dfs);
    rep(i, 0, q)
    {
        int a, b;
        cin >> a >> b;
        a--, b--;
        cout << (ans[rev[a]].test(rev[b]) ? "YES" : "NO") << nL;
    }

    return 0;
}