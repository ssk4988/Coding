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

struct Tree {
	typedef int T;
	static constexpr T unit = -1e9;
	T f(T a, T b) { return max(a, b); } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
        pos += n;
        // cout << pos << " " << sz(s) << endl;
        s[pos] = f(s[pos], val);
		for (; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};
const int inf = 1e7;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n; cin >> n;
        vl a(n);
        rep(i, 0, n) cin >> a[i];
        vl c;
        c.pb(0);
        rep(i, 0, n){
            c.pb(c.back() + a[i]);
        }
        sort(all(c));
        c.erase(unique(all(c)), end(c));
        Tree postree(sz(c)), negtree(sz(c));
        // Node postree(-inf, inf), negtree(-inf, inf);
        auto getidx = [&](ll v) { return lower_bound(all(c), v) - begin(c); };
        map<ll, int> eq;
        ll pref = 0;
        eq[pref] = 0;
        // cout << getidx(pref) << " " << sz(c) << endl;
        postree.update(getidx(pref), 1);
        negtree.update(getidx(pref), -1);
        rep(i, 0, n){
            pref += a[i];
            int idx = getidx(pref);
            int res = -inf;
            if(eq.count(pref)) res = max(eq[pref], res);
            res = max(res, postree.query(0, idx) + i);
            res = max(res, negtree.query(idx+1, sz(c)) - i);
            if(eq.count(pref))
                eq[pref] = max(eq[pref], res);
            else eq[pref] = res;
            postree.update(idx, res - i);
            negtree.update(idx, res + i);
            if(i == n-1) cout << res << "\n";
        }
    }
    
    return 0;
}
