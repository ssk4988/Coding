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
inline ll mod(ll k){
    return k % MOD;
}

struct ModChoose {
	const int LIM;
	vl inv, fact, invfact;
	ModChoose(int n) : LIM(n+1), inv(LIM), fact(LIM), invfact(LIM) {
		fact[0] = invfact[0] = inv[1] = fact[1] = invfact[1] = 1;
		rep(i, 2, LIM) {
			inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
			fact[i] = (i * fact[i - 1]) % MOD;
			invfact[i] = (inv[i] * invfact[i - 1]) % MOD;
		}
	}
	ll choose(int n, int k) {
		if (k > n || k < 0) return 0;
        if(n >= LIM){
            ll ans = 1;
            k = max(k, n - k);
            for(int i = k + 1; i <= n; i++){
                ans = mod(ans * i);
            }
            k = min(k, n - k);
            for(int i = 1; i <= k; i++){
                ans = mod(ans * inv[i]);
            }
            return ans;
        }
        // CHECK LARGE
        // assert(false);
		return (fact[n] * invfact[k]) % MOD * invfact[n - k] % MOD;
	}
    ll allocate(int alloc, int vars) {
        return choose(alloc + vars - 1, vars - 1);
    }
};



int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    ModChoose mc(2e6 + 10);
    rep(cn, 0, nc){
        int n, c; cin >> n >> c;
        vi left(n, -1), right(n, -1);
        vi val(n, -1);
        rep(i, 0, n){
            cin >> left[i] >> right[i] >> val[i];
            if(left[i] > 0) left[i]--;
            if(right[i] > 0) right[i]--;
        }
        vi vals;
        vals.pb(1);
        auto dfs = [&](int u, auto &&dfs) -> void {
            if(left[u] != -1) dfs(left[u], dfs);
            vals.pb(val[u]);
            if(right[u] != -1) dfs(right[u], dfs);
        };
        dfs(0, dfs);
        vals.pb(c);
        int preval = -1, preind = -1;
        ll ans = 1;
        rep(i, 0, sz(vals)){
            if(vals[i] == -1) continue;
            if(preval != -1){
                int bounds = i - preind;
                int dist = vals[i] - preval;
                ans = mod(ans * mc.allocate(dist, bounds));
            }
            preval = vals[i];
            preind = i;
        }
        cout << ans << "\n";
    }
    
    return 0;
}