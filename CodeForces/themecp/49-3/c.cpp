#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

const ll mod = 998244353;
ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    const int LIM = 2e5+10;
    vi lp(LIM+1), primes;

    rep(i, 2, LIM + 1) {
        if (lp[i] == 0) primes.push_back(lp[i] = i);
        for (int j = 0; j < sz(primes) && i * primes[j] <= LIM && primes[j] <= lp[i]; ++j) 
            lp[i * primes[j]] = primes[j];
    }
    vvi fs(LIM);
    rep(i, 2, LIM){
        fs[i] = fs[i / lp[i]];
        fs[i].pb(lp[i]);
    }
    rep(cn, 0, nc) {
        int n; cin >> n;
        vector<vector<tuple<int, ll, ll>>> adj(n);
        rep(i, 0, n-1){
            int u, v; ll a, b; cin >> u >> v >> a >> b; u--, v--;
            adj[u].push_back({v, a, b});
            adj[v].push_back({u, b, a});
        }
        vl me(n);
        me[0] = 1;
        vl num(n+1), denom(n+1), mx(n+1);
        auto dfs = [&](int u, int p, auto &&dfs) -> void {
            for(auto [v, a, b] : adj[u]) {
                if(v == p) continue;
                for(int f : fs[a]) {
                    denom[f] += 1;
                }
                for(int f : fs[b]) {
                    num[f] += 1;
                }
                for(int c : {a, b}){
                    for(int f : fs[c]) {
                        mx[f] = max(mx[f], max(0LL, denom[f] - num[f]));
                    }
                }
                me[v] = b * modpow(a, mod-2) % mod * me[u] % mod;
                dfs(v, u, dfs);
                for(int f : fs[a]) {
                    denom[f] -= 1;
                }
                for(int f : fs[b]) {
                    num[f] -= 1;
                }
            }
        };
        dfs(0, -1, dfs);
        ll sum = 0;
        rep(i, 0, n){
            (sum += me[i]) %= mod;
        }
        rep(i, 1, n+1){
            // if(mx[i]) cout << i << " " << mx[i] << endl;
            rep(j, 0, mx[i]) (sum *= i) %= mod;
        }
        cout << sum << "\n";
    }
    
    return 0;
}
