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
    int n; cin >> n;
    vector<pl> a(n);
    set<int> as;
    rep(i, 0, n){
        cin >> a[i].second >> a[i].first;
        as.insert(a[i].second);
    }
    map<int, int> cca;
    vi av;

    for(int v : as) {
        av.pb(v);
        cca[v] = sz(cca);
    }
    vi compa;
    // for(auto [key, val] : cca) revcca[val] = key;
    sort(all(a));
    rep(i, 0, n) compa.pb(cca[a[i].s]);
    vpl ans(n + 1);
    FT cnts(sz(cca) + 10), vals(sz(cca) + 10);
    auto add = [&](int a, ll v)-> void {
        cnts.update(a, 1);
        vals.update(a, v);
    };
    auto rem = [&](int a, ll v)-> void {
        cnts.update(a, -1);
        vals.update(a, -v);
    };
    auto sumk = [&](int k)-> ll {
        int idx = cnts.lower_bound(k);
        ll presum = vals.query(idx);
        int precnt = cnts.query(idx);
        presum += (k - precnt) * av[idx];
        return presum;
    };
    // cout << "got here" << endl;
    auto solve = [&](int l, int r, int optL, int optR, auto && solve) -> void {
        // l is lower k, r is upper k (exclusive) - k value
        // optl is lower bound of optimal, optr is upper bound of optimal (exclusive) - index of maxb
        // segtree has sum up l (exclusive)0
        // val, index (index is negative so that we can use min)
        if(l >= r) return;
        int mid = l + (r - l) / 2;
        // cout << l << " " << r << " " << optL << " " << optR << " with mid " << mid << endl;
        pl best = {LLONG_MAX, 5};
        int i = optL;
        while(i < mid - 1){
            // cout << i << endl;
            // cout << a[i].s << endl;
            cnts.update(compa[i], 1);
            vals.update(compa[i], a[i].s);

            i++;
        }
        // cout << "made max to left start " << i << endl;
        // i = max(optL, mid - 1)
        for(; i < optR; i++){
            cnts.update(compa[i], 1);
            vals.update(compa[i], a[i].s);

            // cout << "current state: " << i << " " << data.f << endl;
            // assert(data.first >= mid);
            // ll res = sumk(mid);
            int idx = cnts.lower_bound(mid);
            ll res = vals.query(idx);
            int precnt = cnts.query(idx);
            res += (mid - precnt) * av[idx];
            // assert(res.f == mid);
            res += a[i].f;
            best = min(best, {res, -i});
        }
        i--;
        best.s *= -1;
        // assert(best.s >= 0); - fine
        ans[mid] = {best.first, best.s};
        // cout << mid << " " << best.first << " opt: " << best.second << endl;
        while(i >= best.s){
            // rem(compa[i], a[i].s);
            cnts.update(compa[i], -1);
            vals.update(compa[i], -a[i].s);
            i--;
        }
        solve(mid + 1, r, best.s, optR, solve);
        while(i >= optL){
            // rem(compa[i], a[i].s);
            cnts.update(compa[i], -1);
            vals.update(compa[i], -a[i].s);
            i--;
        }
        solve(l, mid, optL, best.s + 1, solve);
    };
    // Node tree(0, sz(cca) + 10);
    solve(1, n + 1, 0, n, solve);
    rep(i, 1, n + 1) cout << ans[i].f << nL; //<< " " << ans[i].s << nL;
    
    return 0;
}