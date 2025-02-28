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
	static constexpr T unit = 0;
	T f(T a, T b) { return max(a, b); } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
        pos += n;
		for (s[pos] = max(s[pos], val); pos /= 2;)
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
        int n; cin >> n;
        vi a(n);
        rep(i, 0, n) {
            cin >> a[i];
        }
        vi c(a);
        sort(all(c));
        c.erase(unique(all(c)), end(c));
        rep(i, 0, n) {
            a[i] = lower_bound(all(c), a[i])-begin(c);
        }
        vector<Tree> trees(3, Tree(sz(c)));
        for(int i : a) {
            for(int j = 2; j >= 0; j--) {
                if(j) trees[j].update(i, 1+trees[j-1].query(0, sz(c)));
                trees[j].update(i, 1+trees[j].query(0, i));
            }
        }
        int ans = 0;
        rep(i, 0, 3) {
            ans = max(ans, trees[i].query(0, sz(c)));
        }
        cout << ans << "\n";
    }

    return 0;
}
