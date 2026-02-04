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

const int inf = 1e9;
using S = pii;
// max left, min right
S ego() {
    return pii{-inf, inf};
}
S op(S a, S b) {
    return pii{max(a.f, b.f), min(a.s, b.s)};
}
using F = int;
S mapping(F f, S s) { return s; }
F id() { return -1; }
F composition(F newer, F older) { return newer; }

struct Tree {
	typedef S T;
	static constexpr T unit = pii{-inf, inf};
	T f(T a, T b) { return op(a, b); } // (any associative fn)
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
    int n, q; cin >> n >> q;
    vi a(n);
    rep(i, 0, n) {
        cin >> a[i];
    }
    vi c(a);
    vector<array<int, 3>> qs(q);
    rep(i, 0, q) {
        rep(j, 0, 3) cin >> qs[i][j];
        if(qs[i][0] == 1) c.pb(qs[i][2]);
    }
    sort(all(c));
    c.erase(unique(all(c)), end(c));
    vector<set<int>> loc(sz(c));
    rep(i, 0, n) {
        a[i] = lower_bound(all(c), a[i])-begin(c);
        loc[a[i]].insert(i);
    }
    rep(i, 0, q) {
        if(qs[i][0] == 1) qs[i][2] = lower_bound(all(c), qs[i][2])-begin(c);
    }
    Tree tree(n);
    auto upd = [&](int u) -> void {
        int left = -inf;
        auto it = loc[a[u]].lower_bound(u);
        if(it != begin(loc[a[u]])){
            left = *prev(it);
        }
        it = next(it);
        int right = inf;
        if(it != end(loc[a[u]])) {
            right = *it;
        }
        tree.update(u, S{left, right});
    };
    rep(i, 0, n) upd(i);
    rep(qid, 0, q) {
        int t = qs[qid][0];
        if(t == 1) {
            int i = qs[qid][1], v = qs[qid][2];
            i--;
            vi upds;
            upds.pb(i);
            loc[a[i]].erase(i);
            auto it = loc[a[i]].lower_bound(i);
            if(it != end(loc[a[i]])) {
                upds.pb(*it);
            }
            if(it != begin(loc[a[i]])) {
                it--;
                upds.pb(*it);
            }
            a[i] = v;
            it = loc[a[i]].lower_bound(i);
            if(it != end(loc[a[i]])) {
                upds.pb(*it);
            }
            if(it != begin(loc[a[i]])) {
                it--;
                upds.pb(*it);
            }
            loc[a[i]].insert(i);
            for(int idx : upds) upd(idx);
        } else {
            int l = qs[qid][1], r = qs[qid][2]; l--;
            S res = tree.query(l, r);
            if(res.f >= l || res.s < r) {
                cout << "NO\n";
            } else cout << "YES\n";
        }
    }
    
    return 0;
}
