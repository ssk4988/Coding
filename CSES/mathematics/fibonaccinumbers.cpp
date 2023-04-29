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
using vvl = vector<vl>;

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

ll MOD = 1e9 + 7;

ll modpow(ll b, ll e, ll m = MOD) {
	ll ans = 1;
    e %= m - 1;
	for (; e; b = b * b % m, e /= 2)
		if (e & 1) ans = ans * b % m;
	return ans;
}

ll mod(ll k){
    return k % MOD;
}

ll modinverse(ll k){
    return modpow(k, MOD - 2);
}

vvl matmul(vvl &a, vvl &b){
    vvl res(sz(a), vl(sz(b[0])));
    rep(i, 0, sz(res)){
        rep(j, 0, sz(res[i])){
            rep(k, 0, sz(a[i])){
                res[i][j] = mod(res[i][j] + mod(a[i][k] * b[k][j]));
            }
        }
    }
    return res;
}

vvl matpow(vvl &m, ll p){
    if(p == 1) return m;
    vvl res = matpow(m, p / 2);
    res = matmul(res, res);
    if(p % 2 == 1) res = matmul(res, m);
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll n; cin >> n;
    vvl fib = {{1, 1}, {1, 0}};
    vvl start = {{1}, {0}};
    if(n <= 1){
        cout << n << nL;
        return 0;
    }
    vvl mult = matpow(fib, n);
    vvl res = matmul(mult, start);
    cout << res[1][0] << nL;
    return 0;
}