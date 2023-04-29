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

ll mod = 1e9 + 7;

ll modpow(ll b, ll e, ll m = mod) {
	ll ans = 1;
    e %= m - 1;
	for (; e; b = b * b % m, e /= 2)
		if (e & 1) ans = ans * b % m;
	return ans;
}

ll modm(ll k){
    return k % mod;
}

ll modinverse(ll k){
    return modpow(k, mod - 2);
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll n; cin >> n;
    ll ans= 0;
    if(n % 2 == 0){
        rep(i, 1, 4 + 1){
            ans = modm(ans + modpow(2,modpow(n / 2, 2, mod - 1) * __gcd(4, i)));
        }
    }
    else{
        ans = modm(ans + 2 * modpow(2,(1LL + (n/2) * (n+1)/2) % (mod - 1)));
        ans = modm(ans + modpow(2,modpow(n, 2, mod - 1)));
        ans = modm(ans + modpow(2,(n/2 * n + (n+1)/2))%(mod - 1));
    }
    cout << modm(ans * modinverse(4)) << nL;
    return 0;
}