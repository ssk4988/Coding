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

const int N = 1e5 + 100;
vi g[N];
vi rg[N], bucket[N];
int sdom[N], par[N], dom[N], dsu[N], label[N];
int arr[N], rev[N], T;
int tree[N];
int Find(int u, int x = 0)
{
    if (u == dsu[u])
        return x ? -1 : u;
    int v = Find(dsu[u], x + 1);
    if (v < 0)
        return u;
    if (sdom[label[dsu[u]]] < sdom[label[u]])
        label[u] = label[dsu[u]];
    dsu[u] = v;
    return x ? v : label[u];
}
void Union(int u, int v) // Add an edge u-->v
{
    dsu[v] = u; // yup,its correct :)
}
void dfs0(int u)
{
    T++;
    arr[u] = T;
    rev[T] = u;
    label[T] = T;
    sdom[T] = T;
    dsu[T] = T;
    for (int i = 0; i < sz(g[u]); i++)
    {
        int w = g[u][i];
        if (!arr[w])
            dfs0(w), par[arr[w]] = arr[u];
        rg[arr[w]].pb(arr[u]);
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m;
    cin >> n >> m;
    rep(i, 0, m)
    {
        int a, b;
        cin >> a >> b;
        g[a].pb(b);
    }
    dfs0(1);
    // n = T;
    for (int i = n; i > 0; i--)
    {
        for (int j = 0; j < sz(rg[i]); j++)
            sdom[i] = min(sdom[i], sdom[Find(rg[i][j])]);
        if (i > 1)
            bucket[sdom[i]].pb(i);
        for (int j = 0; j < sz(bucket[i]); j++)
        {
            int w = bucket[i][j];
            int v = Find(w);
            if (sdom[v] == sdom[w])
                dom[w] = sdom[w];
            else
                dom[w] = v;
        }
        if (i > 1)
            Union(par[i], i);
    }
    for (int i = 2; i <= n; i++)
    {
        if (dom[i] != sdom[i])
            dom[i] = dom[dom[i]];
        tree[rev[i]] = rev[dom[i]];
        // tree[rev[dom[i]]].pb(rev[i]);
    }
    vi ans;
    ans.pb(n);
    while (ans.back() != tree[ans.back()] && ans.back() != 1)
    {
        ans.pb(tree[ans.back()]);
    }
    sort(all(ans));
    if (ans[0] != 1)
        ans.pb(1);
    sort(all(ans));
    cout << sz(ans) << nL;
    for (int i : ans)
        cout << i << " ";
    cout << nL;
    // rep(i, 0, 20){
    //     cout << tree[i] << " dominates " << i << nL;
    // }
    return 0;
}
