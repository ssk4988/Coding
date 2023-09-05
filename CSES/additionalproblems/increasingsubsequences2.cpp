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

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] = mod(s[pos] + dif);
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res = mod(res + s[pos-1]);
		return res;
	}
	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi a(n);
    set<int> ss;
    ss.insert(0);
    unordered_map<int, int> rl;
    rep(i, 0, n){
        cin >> a[i];
        ss.insert(a[i]);
    }
    for(int i : ss) rl[i] = sz(rl);
    FT ft(n + 10);
    ft.update(0, 1);
    rep(i, 0, n){
        a[i] = rl[a[i]];
        ll v = ft.query(a[i]);
        ft.update(a[i], v);
    }
    ll ans = ft.query(n + 5) - ft.query(1);
    while(ans < 0) ans += MOD;
    cout << ans << nL;
    
    return 0;
}
