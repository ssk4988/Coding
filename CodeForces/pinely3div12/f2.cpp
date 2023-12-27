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
		return (fact[n] * invfact[k]) % MOD * invfact[n - k] % MOD;
	}
    ll subgrid(int w, int h, int a){
        // place a elements into wxh grid with no shared rows/columns
        if(a > min(w, h) || min({w, h, a}) < 0) return 0;
        return choose(w, a) * choose(h, a) % MOD * fact[a] % MOD;
    }
};
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ModChoose mc(1e6);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        // ADD MOD
        int n; cin >> n;
        vl a(n + 1);
        ll ans = 1;
        bool works = true;
        int previ = 0, prea = 0;
        rep(i, 1, n + 1){
            cin >> a[i];
            if(a[i] > i) works = false;
            if(i == n && a[i] == -1) a[i] = n;
            if(a[i] != -1){
                if(a[i] < prea) {
                    works = false;
                }
                else{
                    ll mult = 0;
                    int alloc = a[i] - prea;
                    int div = i - previ;
                    int sliv = previ - prea;
                    rep(k, 0, alloc + 1){
                        mult = mod(mult + mod(mc.subgrid(div, sliv, k) * mc.subgrid(div + sliv - k, div, alloc - k)));
                    }
                    ans = mod(ans * mult);
                    previ = i;
                    prea = a[i];
                }
            }
        }
        if(a.back() != n) works = false;
        if(!works) cout << 0 << nL;
        else cout << ans << nL;
    }
    
    return 0;
}
