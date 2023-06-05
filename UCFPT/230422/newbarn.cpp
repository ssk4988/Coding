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

int main()
{
    freopen("newbarn.in", "r", stdin);
    freopen("newbarn.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    vi par;
    vi dep;
    vi treenum;
    vpi diam;
    vvi jump;
    int jmpsz = 25;
    auto lca = [&](int a, int b) -> int
    {
        assert(treenum[a] == treenum[b]);
        if (a == b)
            return a;
        for (int i = jmpsz - 1; i >= 0; i--)
        {
            if (dep[jump[a][i]] >= dep[b])
            {
                a = jump[a][i];
            }
        }
        for (int i = jmpsz - 1; i >= 0; i--)
        {
            if (dep[jump[b][i]] >= dep[a])
            {
                b = jump[b][i];
            }
        }
        for (int i = jmpsz - 1; i >= 0; i--)
        {
            if (jump[b][i] != jump[a][i])
            {
                b = jump[b][i];
                a = jump[a][i];
            }
        }
        while (b != a)
        {
            a = jump[a][0];
            b = jump[b][0];
        }
        return a;
    };
    auto dist = [&](int a, int b) -> int
    {
        assert(treenum[a] == treenum[b]);
        if(a == b) return 0;
        int lc = lca(a, b);
        // int d = 0;
        int d = dep[a] + dep[b] - 2 * dep[lc];
        // if(a != lc && b != lc) d++;
        // cout << "dist from " << a << " to " << b << " via lca of " << lc << " is " << d << nL;
        return d;
    };
    rep(i, 0, n)
    {
        string str;
        cin >> str;
        int k;
        cin >> k;
        k--;
        if (str[0] == 'B')
        {
            int t = sz(par);
            par.pb(k == -2 ? sz(par) : k);
            treenum.pb(k == -2 ? sz(diam) : treenum[k]);
            dep.pb(k == -2 ? 0 : (1 + dep[par[t]]));
            jump.pb(vi(jmpsz));
            jump[t][0] = par[t];
            rep(j, 1, jmpsz)
            {
                jump[t][j] = jump[jump[t][j - 1]][j - 1];
            }
            if (k == -2)
            {
                diam.pb({t, t});
            }
            else
            {
                int further = dist(diam[treenum[t]].f, t) > dist(diam[treenum[t]].s, t) ? diam[treenum[t]].f : diam[treenum[t]].s;
                if(dist(further, t) > dist(diam[treenum[t]].f, diam[treenum[t]].s)){
                    diam[treenum[t]] = {further, t};
                }
            }
        }
        else{
            int further = dist(diam[treenum[k]].f, k) > dist(diam[treenum[k]].s, k) ? diam[treenum[k]].f : diam[treenum[k]].s;
            cout << dist(further, k) << nL;
        }
    }

    return 0;
}
