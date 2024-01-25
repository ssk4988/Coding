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
    ll alloc(int a, int numvars){
        return choose(a + numvars - 1, numvars - 1);
    }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ModChoose mc(int(2e5 + 10));
    int n; cin >> n;
    vl a(n);
    map<int, int> freq;
    ll sum = 0;
    rep(i, 0, n){
        cin >> a[i];
        freq[a[i]]++;
        sum += a[i];
    }
    if(sum % n != 0){
        cout << 0 << nL;
        return 0;
    }
    ll mean = sum / n;
    int pos = 0, neg = 0, equ = 0;
    ll ans = 2;
    for(auto [key, val] : freq){
        ans = mod(ans * mc.invfact[val]);
        if(key > mean) pos += val;
        else if(key == mean) equ += val;
        else neg += val;
    }
    if(equ == n){
        cout << 1 << nL;
    }
    else if(pos == 1 || neg == 1){
        ans = mc.fact[n];
        for(auto [key, val] : freq){
            ans = mod(ans * mc.invfact[val]);
        }
        cout << ans << nL;
    }
    else{
        ans = mod(ans * mc.alloc(equ, pos + neg + 1));
        ans = mod(ans * mc.fact[pos]);
        ans = mod(ans * mc.fact[neg]);
        ans = mod(ans * mc.fact[equ]);
        cout << ans << nL;
    }
    return 0;
}
