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

struct UF
{
    vi e;
    UF(int n) : e(n, -1) {}
    bool sameSet(int a, int b) { return find(a) == find(b); }
    int size(int x) { return -e[find(x)]; }
    int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
    bool join(int a, int b)
    {
        a = find(a), b = find(b);
        if (a == b)
            return false;
        if (e[a] > e[b])
            swap(a, b);
        e[a] += e[b];
        e[b] = a;
        return true;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    vi p(n), inv(n);
    rep(i, 0, n)
    {
        cin >> p[i];
        p[i]--;
        inv[p[i]] = i;
    }
    int need = 0;
    set<int> active, merged;
    vvi adj(n);
    UF uf(n);
    rep(i, 0, n){
        if(p[i] == need){
            // cout << "cleared " << need << ": ";
            need++;
            while(true){
                if(active.count(need)){
                    active.erase(need++);
                    continue;
                }
                if(merged.count(need)){
                    merged.erase(need++);
                    continue;
                }
                // cout << "stopped clearing before " << need << "\n";
                break;
            }
            continue;
        }
        while(sz(active) && *active.begin() < p[i]){
            int x = *active.begin();
            active.erase(x);
            if(sz(merged)) uf.join(x, *merged.begin());
            merged.insert(x);
        }
        if(sz(merged)){
            adj[p[i]].pb(*merged.begin());
            adj[*merged.begin()].pb(p[i]);
        }
        active.insert(p[i]);
    }
    vvi comps(n);
    rep(i, 0, n) comps[uf.find(i)].pb(i);
    vi state(n);
    vi val(n);
    auto dfs = [&](int c, int t, auto &&dfs) -> bool
    {
        if (state[c])
            return val[c] != t;
        state[c] = 1;
        val[c] = t;
        for (int u : comps[c])
            for (int v : adj[u])
                if (dfs(uf.find(v), !t, dfs))
                    return true;
        return false;
    };
    bool imp = false;
    rep(i, 0, n)
    {
        if (sz(comps[i]) && state[i] == 0 && dfs(i, 0, dfs))
            imp = true;
    }
    if (imp)
    {
        cout << "IMPOSSIBLE\n";
    }
    else
    {
        rep(i, 0, n)
        {
            cout << val[uf.find(p[i])] + 1 << " ";
        }
        cout << "\n";
    }

    return 0;
}
