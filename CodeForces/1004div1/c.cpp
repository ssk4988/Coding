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

const ll mod = 1e9+7;

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
    rep(cn, 0, nc) {
        int n; cin >> n;
        vl a(n);
        ll pref = 0;
        rep(i, 0, n) {
            cin >> a[i];
        }

        ll same = 1;
        map<ll, ll> twosame; // stores {ways, time}
        // key is the value that is doubled up on
        // time = 0 is before processing element i
        // auto fix = [&](ll key, ll t) -> void {
        //     auto &[val, prv_time] = twosame[key];
        //     (val *= modpow(2, t - prv_time)) %= mod;
        //     prv_time = t;
        // };
        rep(i, 0, n) {
            // onecnt = pref
            // twocnt to transition is onecnt ^ cur
            ll onev = pref;
            ll pref1 = pref ^ a[i];
            ll nxtsame = 0;
            ll transdouble = pref ^ a[i];
            ll tval = twosame[transdouble];
            ll nxtdouble = transdouble ^ a[i]; // pref
            assert(nxtdouble != transdouble);
            ll makesame = pref ^ a[i];
            nxtsame = twosame[makesame];
            (twosame[nxtdouble] += 2 * tval) %= mod;
            (twosame[pref] += 3 * same) %= mod;
            twosame[pref1] = 0;
            same = nxtsame;
            pref = pref1;
        }
        ll ans = same;
        for(auto [key, val] : twosame) {
            (ans += val) %= mod;
        }
        cout << ans << "\n";
    }
    
    return 0;
}
