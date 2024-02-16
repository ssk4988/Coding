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
#include <bits/extc++.h>
struct chash { // large odd number for C
	const uint64_t C = ll(4e18 * acos(0)) | 71;
	ll operator()(ll x) const { return __builtin_bswap64(x*C); }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, l; cin >> n >> m >> l;
    vpi fishes(n);
    set<int> vals;
    rep(i, 0, n){
        cin >> fishes[i].f >> fishes[i].s;
        vals.insert(fishes[i].s - fishes[i].f);
        vals.insert(fishes[i].f + fishes[i].s);
    }
    sort(all(fishes));
    vpi men(m);
    rep(i, 0, m) {
        cin >> men[i].f;
        vals.insert(l - men[i].f);
        vals.insert(l + men[i].f);
        men[i].s = i;
    }
    sort(all(men));
    __gnu_pbds::gp_hash_table<int,int,chash> cc({},{},{},{},{1<<16});
    // unordered_map<int, int> cc;
    for(int i : vals) cc[i] = sz(cc);
    FT ft(sz(cc));
    int idx = 0;
    vi ans(m);
    rep(i, 0, m){
        while(idx < n && fishes[idx].f <= men[i].f){
            ft.update(cc[fishes[idx].s - fishes[idx].f], 1);
            idx++;
        }
        ans[men[i].s] += ft.query(cc[l - men[i].f] + 1);
    }
    ft = FT(sz(cc));
    idx = n - 1;
    for(int i = m - 1; i >= 0; i--){
        while(idx >= 0 && fishes[idx].f > men[i].f){
            ft.update(cc[fishes[idx].s + fishes[idx].f], 1);
            idx--;
        }
        ans[men[i].s] += ft.query(cc[l + men[i].f] + 1);
    }
    rep(i, 0, m) cout << ans[i] << nL;

    
    return 0;
}