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
    vvl fib(6, vl(6));
    fib[5] = vl(6, 1);
    fib[5][5] = 1;
    rep(i, 0, 5){
        fib[i][i + 1] = 1;
    }
    // 1 1 2 4 8 14 32
    vvl start = {{1}, {2}, {4}, {8}, {16}, {32}};

    // rep(i, 1, 7){
    //     rep(l, 0, 10){
    //         for(int j = 6; j >= 1; j--){
    //             if(j + i >= sz(start)){
    //                 continue;
    //             }
    //             start[j + i][0] += start[j][0];
    //         }

    //     }
    // }
    // rep(i, 0, 7){
    //     cout << start[i][0] << " ";
    // }
    cout << nL;
    if(n <= 1){
        cout << n << nL;
        return 0;
    }
    vvl mult = matpow(fib, n - 1);
    vvl res = matmul(mult, start);
    // rep(i, 0, 6){
    //     cout << res[i][0] << nL;
    // }
    cout << res[0][0] << nL;
    return 0;
}