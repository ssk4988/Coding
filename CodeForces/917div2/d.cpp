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
        int n, k; cin >> n >> k;
        vi p(n), q(k);
        rep(i, 0, n) cin >> p[i];
        rep(i, 0, k) cin >> q[i];
        FT ft(k);
        ll ans = 0;
        rep(i, 0, k){
            ans += n * (ft.query(k) - ft.query(q[i]));
            ft.update(q[i], 1);
        }
        sort(all(q));
        int maxdif = 0;
        // TEST N=1
        int lim = 2 * n - 1;
        for(int p = 1; p < lim; maxdif++, p *= 2);
        vl scplus(maxdif+1), scneg(maxdif+1); // contribution of a[i] on a[j] if a[i] overtakes a[j] in x boosts, or if a[j] overtakes a[i] in x boosts
        rep(i, 1, sz(scplus)){
            int l = k;
            for(int r = k - 1; r >= 0; r--){
                while(l > 0 && q[l - 1] + i > q[r]) l--;
                scneg[i] += k - l;
            }
            l = 0;
            rep(r, 0, k){
                while(l < k && q[l] < q[r] + i) l++;
                scplus[i] += k - l;
            }
        }
        ft = FT(2 * n);
        rep(i, 0, n){
            int div = 2;
            int pre = p[i];
            rep(j, 1, sz(scplus)){
                int cur = p[i] / div;
                while(cur * div < p[i]) cur++;
                ll cnt = ft.query(min(sz(ft.s), pre)) - ft.query(min(sz(ft.s), cur));
                pre = cur;
                div *= 2;
                ans += cnt * scplus[j];
            }
            int mult = 2;
            rep(j, 1, sz(scplus)){
                ll cnt = ft.query(min(sz(ft.s), p[i] * mult)) - ft.query(min(sz(ft.s), p[i] * mult / 2));
                mult *= 2;
                ans += cnt * scneg[j];
            }
            ft.update(p[i], 1);
        }
        cout << ans << nL;
    }
    
    return 0;
}
