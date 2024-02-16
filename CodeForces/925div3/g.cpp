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
    ll multichoose(int alloc, int vars){
        return choose(alloc + vars - 1, vars - 1);
    }
};

const ll MOD = 998244353;
inline ll mod(ll k) {
    return k % MOD;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    const int LIM = 2e6 + 10;
    ModChoose mc(LIM, MOD);
    rep(cn, 0, nc){
        vi c(4);
        rep(i, 0, 4) cin >> c[i];
        if(abs(c[0] - c[1]) > 1){
            cout << 0 << nL;
            continue;
        }
        if(c[0] == 0 && c[1] == 0){
            if(c[2] > 0 && c[3] > 0){
                cout << 0 << "\n";
            }
            else cout << 1 << nL;
            continue;
        }
        ll actualans = 0;
        rep(start, 0, 2){
            if(c[start] && c[start] >= c[1 - start])
            {
                // start with 0 or 1
                ll ans = 1;
                if(c[2]){
                    ll ways = 0;
                    rep(i, 1, min(c[2], c[0]) + 1){
                        ways = mod(ways + mod(mc.choose(c[0], i) * mc.multichoose(c[2] - i, i)));
                    }
                    ans = mod(ans * ways);
                }
                if(c[3]){
                    ll ways = 0;
                    rep(i, 1, min(c[3], c[1]) + 1){
                        ways = mod(ways + mod(mc.choose(c[1], i) * mc.multichoose(c[3] - i, i)));
                    }
                    ans = mod(ans * ways);
                }
                actualans = mod(actualans + ans);
            }
        }

        rep(times, 0, 2){
            if(c[2] && c[1] >= c[0])
            {
                // start with 2
                ll ans = 1;
                c[2]--;
                if(c[2]){
                    ll ways = 0;
                    rep(i, 0, min(c[2], c[0]) + 1){
                        ways = mod(ways + mod(mc.choose(c[0], i) * mc.multichoose(c[2] - i, i + 1)));
                    }
                    ans = mod(ans * ways);
                }
                if(c[3]){
                    ll ways = 0;
                    rep(i, 1, min(c[3], c[1]) + 1){
                        ways = mod(ways + mod(mc.choose(c[1], i) * mc.multichoose(c[3] - i, i)));
                    }
                    ans = mod(ans * ways);
                }
                actualans = mod(actualans + ans);
                c[2]++;
            }
            swap(c[2], c[3]);
            swap(c[0], c[1]);
        }
        cout << actualans << "\n";
    }
    
    return 0;
}