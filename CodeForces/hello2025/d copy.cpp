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
	typedef ll T;
	static constexpr T unit = LLONG_MAX;
	T f(T a, T b) { return min(a, b); } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        int n, q; cin >> n >> q;
        vl a(n);
        Tree ppt(n), pnt(n);
        set<pair<ll, int>> pp, pn;
        rep(i, 0, n){
            cin >> a[i];
            pp.insert({-i + a[i], i});
            pn.insert({-i - a[i], i});
            ppt.update(i, -i + a[i]);
            pnt.update(i, -i - a[i]);
        }
        auto ans = [&]() {
            auto it = prev(end(pp));
            auto it1 = begin(pn);
            return it->f - ppt.query(0, it->s+1);
            // return max(it->f - ppt.query(0, it->s+1), -it1->f - pnt.query(0, it1->s+1));
        };
        cout << ans() << "\n";
        rep(v, 0, q){
            int i, x; cin >> i >> x; i--;
            pp.erase({-i + a[i], i});
            pn.erase({-i - a[i], i});
            a[i] = x;
            pp.insert({-i + a[i], i});
            pn.insert({-i - a[i], i});
            ppt.update(i, -i + a[i]);
            pnt.update(i, -i - a[i]);
            cout << ans() << "\n";
        }
    }
    
    return 0;
}
