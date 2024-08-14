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
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc;
    cin >> nc;
    rep(cn, 0, nc)
    {
        int n, q;
        cin >> n >> q;
        vi par(n);
        par[0] = -1;
        vvi child(n);
        rep(i, 1, n)
        {
            cin >> par[i];
            par[i]--;
            child[par[i]].pb(i);
        }
        vi perm(n), inv(n);
        rep(i, 0, n)
        {
            cin >> perm[i];
            perm[i]--;
            inv[perm[i]] = i;
        }
        auto cmp = [&](int a, int b) -> bool
        {
            return inv[a] < inv[b];
        };
        vector<set<int, decltype(cmp)>> childset(n, set<int, decltype(cmp)>(cmp));
        rep(i, 0, n)
        {
            // rep(i, 0, n) childset[i] = set<int, decltype(cmp)>(cmp);
            for (int v : child[i])
                childset[i].insert(v);
        }
        vi depth(n), subsz(n, 1), fastpar(n, -1); // lowest parent with 2+ child
        vi tin(n);
        int T = 0;
        auto dfs = [&](int u, auto &&dfs) -> void
        {
            tin[u] = T++;
            if (par[u] != -1 && sz(child[par[u]]) < 2)
            {
                fastpar[u] = fastpar[par[u]];
            }
            else
                fastpar[u] = par[u];
            for (int v : child[u])
            {
                depth[v] = 1 + depth[u];
                dfs(v, dfs);
                subsz[u] += subsz[v];
            }
        };
        dfs(0, dfs);
        // cout << 
        vi good(n); // 1st child after me
        vi sib(n);  // sibling after is in right spot
        int goodcnt = 0, sibcnt = 0;
        auto calcgood = [&](int u)
        {
            goodcnt -= good[u];
            good[u] = 1;
            if (sz(childset[u]) > 0)
            {
                auto it = childset[u].begin();
                if (inv[*it] != inv[u] + 1)
                    good[u] = false;
            }
            goodcnt += good[u];
        };
        auto calcsib = [&](int u) {
            sibcnt -= sib[u];
            sib[u] = 1;
            if(par[u] != -1) {
                auto it = childset[par[u]].upper_bound(u);
                if(it != childset[par[u]].end() && inv[u] + subsz[u] != inv[*it]) sib[u] = false;
            }
            sibcnt += sib[u];
        };
        rep(i, 0, n) {
            calcgood(i), calcsib(i);
        }
        rep(i, 0, q)
        {
            int x, y;
            cin >> x >> y;
            x--, y--;
            set<int> recalcgood, recalcsib;
            for (int v : {x, y})
            {
                int u = perm[v];
                recalcgood.insert(u);
                recalcsib.insert(u);
                if (par[u] == -1)
                    continue;
                recalcgood.insert(par[u]);
                auto it = childset[par[u]].lower_bound(u);
                if (it != childset[par[u]].begin())
                    recalcsib.insert(*prev(it));
            }
            for(int v : {x, y}){
                int u = perm[v];
                if(par[u] == -1) continue;
                childset[par[u]].erase(u);
            }
            swap(perm[x], perm[y]);
            swap(inv[perm[x]], inv[perm[y]]);
            for (int v : {x, y})
            {
                int u = perm[v];
                if (par[u] == -1)
                    continue;
                childset[par[u]].insert(u);
            }
            for (int v : {x, y})
            {
                int u = perm[v];
                if (par[u] != -1)
                {
                    auto it = childset[par[u]].lower_bound(u);
                    if (it != childset[par[u]].begin())
                        recalcsib.insert(*prev(it));
                }
            }
            for(int u : recalcgood) calcgood(u);
            for(int u : recalcsib) calcsib(u);
            cout << (goodcnt == n && sibcnt == n ? "YES" : "NO") << "\n";
        }
    }

    return 0;
}
