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

const ll MOD = 1e9 + 7;

ll mod(ll k){
    return k % MOD;
}

ll mod1(ll k){
    return (k % MOD + MOD) % MOD;
}

struct ModChoose {
	const ll MOD;
	const int LIM;
	vl inv, fact, invfact;
	ModChoose(int n, ll m) : LIM(n+1), MOD(m), inv(LIM), fact(LIM), invfact(LIM) {
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
    ll starsbars(int num, int vars){
        return choose(num + vars - 1, vars - 1);
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    ModChoose c(4e5 + 100, 1e9 + 7);
    rep(cn, 0, nc){
        int n0, n1, l0, r0, l1, r1; cin >> n0 >> n1 >> l0 >> r0 >> l1 >> r1;
        ll ans = 0;
        int min0 = (n0 + r0 - 1) / r0, max0 = n0 / l0;
        int min1 = (n1 + r1 - 1) / r1, max1 = n1 / l1;
        vl ways0(max0 + 1), ways1(max1 + 1);
        for(int num0 = min0; num0 <= max0; num0++){
            int dif = r0 - l0 + 1;
            rep(i, 0, num0 + 1){
                int numleft = n0 - i * (r0 + 1) - (num0 - i) * l0;
                if(numleft < 0) continue;
                ways0[num0] = mod(ways0[num0] + mod1((i % 2 == 0 ? 1 : -1) * mod(c.choose(num0, i) * c.starsbars(numleft, num0))));
            }
        }
        for(int num1 = min1; num1 <= max1; num1++){
            int dif = r1 - l1 + 1;
            rep(i, 0, num1 + 1){
                int numleft = n1 - i * (r1 + 1) - (num1 - i) * l1;
                if(numleft < 0) continue;
                ways1[num1] = mod(ways1[num1] + mod1((i % 2 == 0 ? 1 : -1) * mod(c.choose(num1, i) * c.starsbars(numleft, num1))));
            }
        }
        // cout << min0 << " " << max0 << " " << min1 << " " << max1 << nL;
        for(int num0 = min0; num0 <= max0; num0++){
            for(int add = -1; add <= 1; add++){
                int num1 = add + num0;
                if(num1 < min1 || max1 < num1) continue;
                // cout << num0 << " " << num1 << nL;
                ll cont = mod(ways0[num0] * ways1[num1]);
                if(add == 0){
                    cont = mod(cont * 2);
                }
                ans = mod(ans + cont);
            }
        }
        cout << ans << nL;
    }
    
    return 0;
}