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

#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

struct Tree {
	typedef int T;
	static constexpr T unit = INT_MAX;
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
    void clear() { fill(all(s), unit); }
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi h(n);
    rep(i, 0, n){
        cin >> h[i];
    }
    int hs;
    {
        vi c(h);
        sort(all(c));
        hs = sz(c);
        c.erase(unique(all(c)), end(c));
        for(int &i : h) i = lower_bound(all(c), i) - begin(c);
    }
    int q; cin >> q;
    vector<priority_queue<pii, vii, greater<>>> qs(hs); // {ans[i], i}
    Tree tree(hs);
    rep(_, 0, q){
        int k; cin >> k;
        tree.clear();
        vi ans(n, 1e9);
        ans[0] = 0;
        rep(i, 0, n){
            int down = tree.query(h[i]+1, hs);
            int up = tree.query(0, h[i]+1);
            if(down != tree.unit) ans[i] = min(ans[i], down);
            if(up != tree.unit) ans[i] = min(ans[i], 1 + up);
            if(i >= k){
                while(sz(qs[h[i - k]]) && qs[h[i - k]].top().second <= i - k) qs[h[i - k]].pop();
                tree.update(h[i - k], sz(qs[h[i - k]]) ? qs[h[i - k]].top().first : tree.unit);
            }
            while(sz(qs[h[i]]) && qs[h[i]].top().first >= ans[i]) qs[h[i]].pop();
            qs[h[i]].push({ans[i], i});
            tree.update(h[i], sz(qs[h[i]]) ? qs[h[i]].top().first : tree.unit);
        }
        cout << ans[n-1] << "\n";
        rep(i, 0, hs) while(sz(qs[i])) qs[i].pop();
    }
    
    return 0;
}
