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
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
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
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, k, d; cin >> n >> k >> d;
        vi a(n);
        rep(i, 0, n){
            cin >> a[i];
            a[i] -= i + 1;
            a[i] = -a[i];
        }
        vi v(k);
        rep(i, 0, k){
            cin >> v[i]; v[i]--;
        }
        int moves = min(d, 2 * n + 5);
        FT ft(moves);
        vpi order;
        rep(i, 0, moves){
            order.pb({v[i % k], i + 1});
        }
        sort(all(order));
        reverse(all(order));
        int pnt = 0;
        vi sc(moves);
        for(int i = n - 1; i >= 0; i--){
            while(pnt < sz(order) && order[pnt].f >= i){
                ft.update(order[pnt].s, 1);
                pnt++;
            }
            if(a[i] < 0) continue;
            int idx = a[i] == 0 ? 0 : ft.lower_bound(a[i]);
            if(idx >= moves) continue;
            sc[idx]++;
            idx = ft.lower_bound(a[i] + 1);
            if(idx < sz(sc)) sc[idx]--;
        }
        int ans = 0;
        rep(i, 0, moves){
            // i is num increases before start alternating count and increase
            if(i) sc[i] += sc[i-1];
            ans = max(ans, sc[i] + (d - 1 - i) / 2);
        }
        cout << ans << nL;
    }
    
    return 0;
}
