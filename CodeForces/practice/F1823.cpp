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

const ll MOD = 998244353;

inline ll mod(ll k) { return k % MOD; }
ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % MOD, e /= 2)
		if (e & 1) ans = ans * b % MOD;
	return ans;
}
ll modinv(ll b){
    return modpow(b, MOD-2);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, s, t; cin >> n >> s >> t; s--, t--;
    vvi adj(n);
    rep(i, 0, n-1){
        int u, v; cin >> u >> v; u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    vi adjcnt(n);
    vpl par(n);
    vl ans(n, -1);
    auto dfs = [&](int u, int p, auto &&dfs)->void {
        if(u == t){
            return;
        }
        adjcnt[u] = sz(adj[u]);
        for(int v : adj[u]) if(v != p){
            dfs(v, u, dfs);
        }
    };
    dfs(s, -1, dfs);
    auto getpar = [&](int u, int p, auto &&getpar) ->void {
        auto &[pmult, add] = par[u];
        if(adjcnt[u] == 0) return;
        add = u == s;
        ll mmult = 0, cadd = 0;
        for(int v : adj[u]) if(v != p) {
            getpar(v, u, getpar);
            if(adjcnt[v] == 0) continue;
            mmult = mod(mmult + mod(par[v].f * mod(modinv(adjcnt[v])))); 
            cadd = mod(cadd + mod(par[v].s * mod(modinv(adjcnt[v]))));
        }
        pmult = adjcnt[p] == 0 ? 0 : modinv(adjcnt[p]);
        add = mod(add + cadd);
        mmult = mod(1 - mmult);
        add = mod(add * modinv(mmult));
        pmult = mod(pmult * modinv(mmult));
        mmult = 1;
    };
    for(int v : adj[t]) getpar(v, t, getpar);
    ans[t] = 1;
    auto go = [&](int u, int p, auto &&go) -> void {
        if(p != -1){
            ans[u] = mod(mod(par[u].f * ans[p]) + par[u].s);
        }
        for(int  v: adj[u]) if(v != p) {
            go(v, u, go);
        }
    };
    go(t, -1, go);
    rep(i, 0, n){
        ans[i] = mod(ans[i] + MOD);
        cout << ans[i] << " ";
    }
    cout << "\n";

    
    return 0;
}
