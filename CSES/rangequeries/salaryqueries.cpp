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

struct FT {
	ll s[1'000'000];
	int n = 1'000'000;
	FT(){
		memset(s, 0, sizeof s);
	}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < n; pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= n && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    vi a(n);
	vi cc;
    rep(i, 0, n){
        cin >> a[i];
		cc.pb(a[i]);
    }
	vvi qs(q);
	rep(i, 0, q){
		char c; int a, b; cin >> c >> a >> b;
		qs[i].pb(c == '!' ? 0 : 1);
		qs[i].pb(a);qs[i].pb(b);
		cc.pb(b);
		if(c == '?') cc.pb(a);
	}
	sort(all(cc));
	cc.erase(unique(all(cc)), end(cc));
	rep(i, 0, n){
		a[i] = lower_bound(all(cc), a[i])-begin(cc);
	}
	rep(i, 0, q){
		if(qs[i][0] == 1) qs[i][1] = lower_bound(all(cc), qs[i][1])-begin(cc);
		else qs[i][1]--;
		qs[i][2] = lower_bound(all(cc), qs[i][2])-begin(cc);
	}
    FT ft;
    rep(i, 0, n){
        ft.update(a[i], 1);
    }
    rep(i, 0, q){
		if(qs[i][0] == 1){
			cout << (ft.query(qs[i][2] + 1) - ft.query(qs[i][1])) << nL;
		}
		else{
			ft.update(a[qs[i][1]], -1);
			a[qs[i][1]] = qs[i][2];
			ft.update(a[qs[i][1]], 1);
		}
	}
    
    return 0;
}
