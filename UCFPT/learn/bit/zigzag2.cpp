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

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) (s[pos] += dif) %= MOD;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) (res += s[pos-1]) %= MOD;
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
        int n; cin >> n;
        vi a(n);
        rep(i, 0, n){
            cin >> a[i];
        }
        int lim = n + 5;
        vi a2(a);
        a2.pb(-1e9 - 10);
        sort(all(a2));
        a2.erase(unique(all(a2)), a2.end());
        vector<FT> nexinc(4, FT(lim)), nexdec(4, FT(lim));
        nexinc[0].update(0, 1), nexdec[0].update(lim-1, 1);
        rep(i, 0, n){
            a[i] = lower_bound(all(a2), a[i]) - a2.begin();
        }
        rep(i, 0, n){
            rep(j, 1, 4){
                ll inc = nexinc[j-1].query(a[i]), dec = mod(MOD + nexdec[j-1].query(lim) - nexdec[j-1].query(a[i]+1));
                if(j == 3){
                    inc = mod(inc + nexinc[j].query(a[i]));
                    dec = mod(dec + MOD + nexdec[j].query(lim) - nexdec[j].query(a[i]+1));
                }
                nexdec[j].update(a[i], inc), nexinc[j].update(a[i], dec);
            }
        }
        ll ans = nexdec[3].query(lim) + nexinc[3].query(lim) + MOD;
        ans = mod(ans);
        cout << ans << "\n";
    }
    
    return 0;
}
