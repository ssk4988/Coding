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

void solve() {
    int n; cin >> n;
    vl h(n);
    vpl hs;
    rep(i, 0, n){
        cin >> h[i];
        hs.push_back({h[i], i});
    }
    vvi adj(n);
    rep(i, 0, n-1){
        int u, v; cin >> u >> v; u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vi par(n, -1);
    auto dfs = [&](int u, int p, auto &&dfs) -> void {
        par[u] = p;
        for(int v : adj[u]){
            if(v == p) continue;
            dfs(v, u, dfs);
        }
    };
    sort(all(hs));
    reverse(all(hs));
    vi marked(n);
    vvi st(n);
    dfs(hs[0].s, -1, dfs);
    marked[hs[0].second] = 1;
    st[hs[0].second].pb(hs[0].f);
    st[hs[0].second].pb(hs[0].f);
    rep(a, 1, n){
        auto [x, i] = hs[a];
        if(marked[i]) continue;
        // marked[i] = true;
        int v = i;
        while(!marked[v]){
            marked[v] = true;
            v = par[v];
        }
        if(sz(st[v]) && st[v].back() == x) st[v].pop_back();
        st[i].pb(x);
    }
    auto calc = [&](int u, int p, auto &&calc) -> pl {
        vl bestc;
        ll res = 0;
        for(int v : adj[u]) {
            if(v == p) continue;
            auto [sm, mx] = calc(v, u, calc);
            res += sm;
            bestc.pb(mx);
        }
        for(auto x : st[u]) res += x;
        sort(rbegin(bestc), rend(bestc));
        // while(sz(st[u]) > 1) st[u].pop_back();
        int pnt = 0;
        for(auto x : st[u]) {
            while(pnt < sz(bestc) && bestc[pnt] == x) {
                pnt++;
            }
            if(pnt < sz(bestc)) res -= bestc[pnt++];
        }
        // rep(i, 0, min(sz(bestc), sz(st[u]))){
        //     if(st[u][i] != bestc[i]) res -= bestc[i];
        // }
        return {res, max({sz(bestc) ? bestc[0] : 0LL, sz(st[u]) ? st[u][0] : 0LL})};
    };
    auto [sm, mx] = calc(hs[0].s, -1, calc);
    cout << sm << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    // int nc; cin >> nc;
    // rep(cn, 0, nc) 
    solve();
    
    return 0;
}
