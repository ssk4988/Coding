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
    vector<set<pi>> ss;
    UF(int n, vi &r) : e(n, -1), ss(n) {
        rep(i, 0, n) ss[i].insert({r[i], i});
    }
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
        for(auto [R, i] : ss[b]) ss[a].insert({R, i});
        ss[b].clear();
        return true;
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n;
    cin >> n;
    vi p(n);
    vi l(n, -1), r(n, -1);
    int T = 0;
    int solve = 0;
    vi seen(n);
    rep(i, 0, n)
    {
        cin >> p[i];
        p[i]--;
        seen[p[i]] = true;
        l[p[i]] = T++;
        while(solve < n && seen[solve]){
            r[solve] = T++;
            solve++;
        }
    }
    // int need = 0;
    // set<int> active, merged;
    vvi adj(n);
    UF uf(n, r);
    vector<array<int, 3>> rs;
    rep(i, 0, n) rs.pb({l[i], r[i], i});
    sort(all(rs));
    priority_queue<pi, vpi, greater<>> pq;
    for(auto [L, R, i] : rs) {
        while(sz(pq) && pq.top().f < L) {
            auto [r1, idx1] = pq.top(); pq.pop();
            int u = uf.find(idx1);
            auto it = uf.ss[u].upper_bound({r1, idx1});
            if(it != end(uf.ss[u])){
                pq.push(*it);
            }
        }
        vpi other;
        while(sz(pq) && pq.top().f < R) {
            auto [r1, idx] = pq.top(); pq.pop();
            other.pb({r1, idx});
        }
        rep(j, 1, sz(other)){
            uf.join(other[j-1].s, other[j].s);
        }
        if(sz(other)){
            adj[i].pb(other[0].s);
            adj[other[0].s].pb(i);
            int u = uf.find(other[0].s);
            auto it = uf.ss[u].upper_bound({L, -1});
            if(it != end(uf.ss[u])){
                pq.push(*it);
            }
        }
        pq.push({R, i});
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
        // cout << "Bipartite failed" << "\n";
        return 0;
    }
    vvi st(2);
    solve = 0;
    rep(i, 0, n){
        int v = p[i];
        int c = val[uf.find(v)];
        if(sz(st[c]) && st[c].back() < v){
            imp = true;
            break;
        }
        st[c].pb(v);
        while(solve < n && ((sz(st[0]) && st[0].back() == solve) || (sz(st[1]) && st[1].back() == solve))) {
            if(sz(st[0]) && st[0].back() == solve) st[0].pop_back();
            else st[1].pop_back();
            solve++;
        }
    }
    if(solve != n) imp = true;
    if(imp) cout << "IMPOSSIBLE\n";
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
